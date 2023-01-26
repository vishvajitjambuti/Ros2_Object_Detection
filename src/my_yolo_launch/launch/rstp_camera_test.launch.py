from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    ld = LaunchDescription()
    
    undistorted_img_1 = Node(
        package='my_undistort_img_pkg',
        executable='undistort_img1',
        name='undistorted_img_1',
        remappings=[('/undistorded/image_raw_1', 'img_1')]
    )
    undistorted_img_2 = Node(
        package='my_undistort_img_pkg',
        executable='undistort_img2',
        name='undistorted_img_2',
        remappings=[('/undistorded/image_raw_2', 'img_2')]
    )
    undistorted_img_3 = Node(
        package='my_undistort_img_pkg',
        executable='undistort_img3',
        name='undistorted_img_3',
        remappings=[('/undistorded/image_raw_3', 'img_3')]
    )
    undistorted_img_4 = Node(
        package='my_undistort_img_pkg',
        executable='undistort_img4',
        name='undistorted_img_4',
        remappings=[('/undistorded/image_raw_4', 'img_4')]
    )
    ld.add_action(undistorted_img_1)
    ld.add_action(undistorted_img_2)
    ld.add_action(undistorted_img_3)
    ld.add_action(undistorted_img_4)
    
    return ld


