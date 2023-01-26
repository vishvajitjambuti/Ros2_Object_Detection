from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    ld = LaunchDescription()
    
    
    
    object_detection = Node(
        package='my_yolov5_pkg',
        executable="yolo_4cam_detect",
        name='object_detection_node',
        
    )
    
    
    ld.add_action(object_detection)
    
    return ld