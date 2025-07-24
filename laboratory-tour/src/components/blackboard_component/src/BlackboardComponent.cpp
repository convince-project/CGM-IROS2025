/******************************************************************************
 *                                                                            *
 * Copyright (C) 2020 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/


#include "BlackboardComponent.h"

bool BlackboardComponent::start(int argc, char*argv[])
{

    if(!rclcpp::ok())
    {
        rclcpp::init(/*argc*/ argc, /*argv*/ argv);
    }
    m_node = rclcpp::Node::make_shared("BlackboardComponentNode");
    
    m_setIntService = m_node->create_service<blackboard_interfaces_dummy::srv::SetIntBlackboard>("/BlackboardComponent/SetInt",  
                                                                                std::bind(&BlackboardComponent::SetInt,
                                                                                this,
                                                                                std::placeholders::_1,
                                                                                std::placeholders::_2));
    m_getIntService = m_node->create_service<blackboard_interfaces_dummy::srv::GetIntBlackboard>("/BlackboardComponent/GetInt",  
                                                                                std::bind(&BlackboardComponent::GetInt,
                                                                                this,
                                                                                std::placeholders::_1,
                                                                                std::placeholders::_2));

    RCLCPP_DEBUG(m_node->get_logger(), "BlackboardComponent::start");
    std::cout << "BlackboardComponent::start" << std::endl;        
    return true;

}

bool BlackboardComponent::close()
{
    rclcpp::shutdown();  
    return true;
}

void BlackboardComponent::spin()
{
    rclcpp::spin(m_node);  
}


void BlackboardComponent::GetInt( const std::shared_ptr<blackboard_interfaces_dummy::srv::GetIntBlackboard::Request> request,
             std::shared_ptr<blackboard_interfaces_dummy::srv::GetIntBlackboard::Response>      response) 
{
    std::string field_name = "PoiDone" + std::to_string(request->field_name);
    // std::cout << "GetInt Request: " << request->field_name << "translation " << field_name << std::endl; 

    std::scoped_lock<std::mutex> lock(m_mutexInt);
    auto it = m_intBlacboard.find(field_name);
    if (it == m_intBlacboard.end()) {
        response->is_ok = false;
    } else {
        response->value = it->second;
        response->is_ok = true;
    }
    
}


void BlackboardComponent::SetInt( const std::shared_ptr<blackboard_interfaces_dummy::srv::SetIntBlackboard::Request> request,
             std::shared_ptr<blackboard_interfaces_dummy::srv::SetIntBlackboard::Response>      response) 
{

    std::string field_name = "PoiDone" + std::to_string(request->field_name);

    if(request->field_name < 0)
    {
        response->is_ok = false;
    } else {

        std::scoped_lock<std::mutex> lock(m_mutexInt);
        m_intBlacboard.insert_or_assign(field_name, request->value); 
        // std::cout << "SetInt: " << field_name << " " << request->value << std::endl; 
        response->is_ok = true;
    }
    

}
