/******************************************************************************
 *                                                                            *
 * Copyright (C) 2020 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

#include <mutex>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32.hpp>
#include <atomic>
#include <vector>
#include <yarp/os/Network.h>
#include <yarp/os/LogStream.h>
#include <yarp/os/RFModule.h>
#include <yarp/os/RpcClient.h>
#include <sensor_msgs/msg/battery_state.hpp>

class BatteryComponent
{
public:
    BatteryComponent() = default;

    bool start(int argc, char*argv[]);

    bool close();
    void spin();
    bool getCharge(int&);
    void BatteryStateSubscriptionCallback(const sensor_msgs::msg::BatteryState::SharedPtr msg);
    void BatteryStatePublisherCallback();


private:
    rclcpp::Node::SharedPtr m_node;
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr m_publisherBatteryState;
    rclcpp::TimerBase::SharedPtr m_timer;
    rclcpp::Subscription<sensor_msgs::msg::BatteryState>::SharedPtr m_subscriptionBatteryState;
    std::atomic<bool> m_batteryCharging{false};
    float m_batteryLevel{100.0};
    std::mutex m_mutex;
    std::queue<double> m_lastBatteryVoltagesBeforeChange;
    std::queue<double> m_lastBatteryVoltagesAfterChange;
    bool m_changeDetected{false};
};
