/******************************************************************************
 *                                                                            *
 * Copyright (C) 2023 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/
/**
 * @file ROS2Action.h
 * @authors: Stefano Bernagozzi <stefano.bernagozzi@iit.it>
 */

#pragma once


#include <string>
#include <bt_interfaces_dummy/msg/action_response.hpp>
#include <mutex>
#include <bt_interfaces_dummy/srv/tick_action.hpp>
#include <bt_interfaces_dummy/srv/halt_action.hpp>
#include <rclcpp/rclcpp.hpp>
#include <behaviortree_cpp_v3/action_node.h>
#include <rcl/service_introspection.h>

class ROS2Action :  public BT::ActionNodeBase
{
public:
    ROS2Action (const std::string name, const BT::NodeConfiguration &config);
    int sendTickToSkill();
    void halt() override;
    BT::NodeStatus tick() override;
    bool init();
    bool stop();
    static BT::PortsList providedPorts();

private:
    std::mutex m_requestMutex;
    rclcpp::Client<bt_interfaces_dummy::srv::TickAction>::SharedPtr m_clientTick;
    rclcpp::Client<bt_interfaces_dummy::srv::HaltAction>::SharedPtr m_clientHalt;
    std::shared_ptr<rclcpp::Node> m_node;
    std::string m_name;
    std::string m_suffixMonitor;
    double m_average_time = 0;
    int m_tick_count = 0;
};

