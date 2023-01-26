from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    ld = LaunchDescription()
    src_1 = "rtsp://192.168.73.10:8554/h264"
    camera_publisher_node_1 = Node(
        package='my_camera_pkg',
        executable='camera_stride_pub',
        name='camera_publisher_node_1',
        remappings=[('image_raw', 'img_1')],
        parameters=[{'camera_id': src_1}, {'vid_stride': 30}]
        )
    
    camera_publisher_node_2 = Node(
        package='my_camera_pkg',
        executable='camera_stride_pub',
        name = 'camera_publisher_node_2',
        remappings=[('image_raw', 'img_2')],
        parameters=[{'camera_id': src_1}, {'vid_stride': 30}]
        )
    
    two_camera_subscriber_node = Node(
        package='my_camera_pkg',
        executable='2camera_sub',
        name = 'two_camera_subscriber_node',
        
        )
    
    camera_sub = Node(
        package='my_camera_pkg',
        executable='camera_sub',
        remappings=[('image_raw', 'img_1')],
    )
    ld.add_action(camera_publisher_node_1)
    ld.add_action(camera_sub)
    #ld.add_action(camera_publisher_node_2)
    #ld.add_action(two_camera_subscriber_node)
    
    
    return ld