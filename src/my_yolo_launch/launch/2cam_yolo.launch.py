from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    ld = LaunchDescription()
    
    src_1 = 0
    src_2 = 2
    
    
    camera_publisher_node_1 = Node(
        package='my_camera_pkg',
        executable='camera_stride_pub',
        name='camera_publisher_node_1',
        remappings=[('image_raw', 'img_1')],
        parameters=[{'camera_id': src_1}, {'vid_stride': 10}]
        )
    
    camera_publisher_node_2 = Node(
        package='my_camera_pkg',
        executable='camera_stride_pub',
        name = 'camera_publisher_node_2',
        remappings=[('image_raw', 'img_2')],
        parameters=[{'camera_id': src_2}, {'vid_stride': 10}]
        )
    
    
    object_detection_node = Node(
        package='my_yolov5_pkg',
        executable='yolo_2cam_detect',
        name = 'object_detection_node',
    )
    camera_sub_1 = Node(
        package="my_camera_pkg",
        executable="camera_sub",
        name="camera_sub_1",
        remappings=[('image_raw', '/yolov5/image_raw_1')],
        parameters=[{'window_name': "camera_sub_1"}]
    )
    camera_sub_2 = Node(
        package="my_camera_pkg",
        executable="camera_sub",
        name="camera_sub_2",
        remappings=[('image_raw', '/yolov5/image_raw_2')],
        parameters=[{'window_name': "camera_sub_2"}]
    )
    
    ld.add_action(camera_publisher_node_1)
    # ld.add_action(camera_sub)
    ld.add_action(camera_publisher_node_2)
    ld.add_action(object_detection_node)
    ld.add_action(camera_sub_1)
    ld.add_action(camera_sub_2)
    
    return ld
    