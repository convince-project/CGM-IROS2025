/******************************************************************************
 *                                                                            *
 * Copyright (C) 2020 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/


#include "BatteryComponent.h"

bool BatteryComponent::start(int argc, char*argv[])
{
    if(!rclcpp::ok())
    {
        rclcpp::init(/*argc*/ argc, /*argv*/ argv);
    }
    m_node = rclcpp::Node::make_shared("BatteryComponentNode");
    m_subscriptionBatteryState = m_node->create_subscription<sensor_msgs::msg::BatteryState>("/battery_status", 
                                                                                             10, 
                                                                                             std::bind(&BatteryComponent::BatteryStateSubscriptionCallback, 
                                                                                                       this, 
                                                                                                       std::placeholders::_1)
                                                                                             );
    m_publisherBatteryState = m_node->create_publisher<std_msgs::msg::Int32>("/BatteryComponent/battery_level", 10);
    m_timer = m_node->create_wall_timer(std::chrono::seconds(1), std::bind(&BatteryComponent::BatteryStatePublisherCallback, this));
    RCLCPP_INFO(m_node->get_logger(), "BatteryComponent::start");
    return true;

}

bool BatteryComponent::getCharge(int& charge)
{
    // Create a port to communicate with /fakeBattery/rpc
    yarp::os::RpcClient batteryPort;

    // Connect to the RPC port
    if (!batteryPort.open("/myBatteryClient")) {
        std::cerr << "Error: Could not open port /myBatteryClient." << std::endl;
        return false;
    }

    if (!yarp::os::Network::connect("/myBatteryClient", "/fakeBattery/rpc")) {
        std::cerr << "Error: Could not connect to /fakeBattery/rpc." << std::endl;
        batteryPort.close();
        return false;
    }

    // Create a bottle to send the RPC command
    yarp::os::Bottle cmd, response;
    cmd.addString("getBatteryCharge");

    // Send the command and wait for a response
    if (!batteryPort.write(cmd, response)) {
        std::cerr << "Error: Failed to write to the /fakeBattery/rpc port." << std::endl;
        return false;
    } else {
        // Check if response is valid
        if (response.size() > 0) {
            std::cout << "Battery charge: " << response.toString() << std::endl;
            charge = response.get(0).asInt32();
            return true;
        } else {
            std::cerr << "Error: Empty response from /fakeBattery/rpc." << std::endl;
            return false;
        }
    }
    
}

bool BatteryComponent::close()
{
    rclcpp::shutdown();  
    return true;
}

void BatteryComponent::spin()
{
    rclcpp::spin(m_node);  
}


void BatteryComponent::BatteryStateSubscriptionCallback(const sensor_msgs::msg::BatteryState::SharedPtr msg)
{
    RCLCPP_INFO_STREAM(m_node->get_logger(), "BatteryChargingComponent::BatteryStateSubscriptionCallback Percentage: " << msg->percentage);
    float percentage = msg->percentage;
    m_mutex.lock();
    // the real battery level is not stable, so we use an isteresi method to avoid flickering
    if(m_batteryLevel <= 30.0 && percentage < 35.0 && percentage > 30.0)
    {
        m_batteryLevel = 30.0;
    }
    else
    {
        m_batteryLevel = percentage;
    }
    m_mutex.unlock();
}


void BatteryComponent::BatteryStatePublisherCallback()
{
    std_msgs::msg::Int32 msg;
    int charge;
    // getCharge(charge);
    m_mutex.lock();
    msg.data = static_cast<int>(m_batteryLevel);
    m_mutex.unlock();
    // msg.data = charge;
    m_publisherBatteryState->publish(msg);
}
