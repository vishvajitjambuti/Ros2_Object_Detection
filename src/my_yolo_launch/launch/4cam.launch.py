from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    ld = LaunchDescription()
    
    undistorded_camera_publisher_node_1 = Node(
        package='my_undistort_img_pkg',
        executable='undistort_img1',
        parameters=[{'wall_timer': 10}],
        remappings=[('/undistorded/image_raw_1', 'img_1')],
    )
    undistorded_camera_publisher_node_2 = Node(
        package='my_undistort_img_pkg',
        executable='undistort_img2',
        parameters=[{'wall_timer': 10}],
        remappings=[('/undistorded/image_raw_2', 'img_2')],
    )
    undistorded_camera_publisher_node_3 = Node(
        package='my_undistort_img_pkg',
        executable='undistort_img3',
        parameters=[{'wall_timer': 10}],
        remappings=[('/undistorded/image_raw_3', 'img_3')],
    )
    undistorded_camera_publisher_node_4 = Node(
        package='my_undistort_img_pkg',
        executable='undistort_img4',
        parameters=[{'wall_timer': 10}],
        remappings=[('/undistorded/image_raw_4', 'img_4')],
    )
    ld.add_action(undistorded_camera_publisher_node_1)
    ld.add_action(undistorded_camera_publisher_node_2)
    ld.add_action(undistorded_camera_publisher_node_3)
    ld.add_action(undistorded_camera_publisher_node_4)
    
    return ld
