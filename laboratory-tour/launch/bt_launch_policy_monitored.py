from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='bt_executable',
            executable='bt_executable',
            arguments=[ './src/behavior_tree/BT/Policy_monitored.xml']
        ), 
    ])

