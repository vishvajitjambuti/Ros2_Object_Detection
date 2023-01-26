from launch import LaunchDescription
from launch_ros.actions import Node
import time
def generate_launch_description():
    ld = LaunchDescription()
    
    camera_sub_node_1 = Node(
        package='my_camera_pkg',
        executable='camera_sub',
        name='camera_sub_node_1',
        remappings=[('image_raw', 'img_1')],
        parameters=[ {'window_name': "front"}]
        )
    camera_sub_node_2 = Node(
        package='my_camera_pkg',
        executable='camera_sub',
        name='camera_sub_node_1',
        remappings=[('image_raw', 'img_2')],
        parameters=[ {'window_name': "left"}]
        )
    camera_sub_node_3 = Node(
        package='my_camera_pkg',
        executable='camera_sub',
        name='camera_sub_node_1',
        remappings=[('image_raw', 'img_4')],
        parameters=[ {'window_name': "back"}]
        )
    camera_sub_node_4 = Node(
        package='my_camera_pkg',
        executable='camera_sub',
        name='camera_sub_node_1',
        remappings=[('image_raw', 'img_4')],
        parameters=[ {'window_name': "right"}]
        )
    ld.add_action(camera_sub_node_1)
    ld.add_action(camera_sub_node_2)
    
    ld.add_action(camera_sub_node_3)
    ld.add_action(camera_sub_node_4)
    return ld
    