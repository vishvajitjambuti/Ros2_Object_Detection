from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import launch.actions

def generate_launch_description():
    ld = LaunchDescription()
    
    remap_camera_topic1 = ('image_raw', 'cam_1')
    camera_publisher_node = Node(
        package='my_camera_pkg',
        executable='camera_stride_pub',
        remappings=[remap_camera_topic1],
        parameters=[{'camera_id': 0}]
         
                )
    included_launch = launch.actions.IncludeLaunchDescription(launch.launch_description_sources.PythonLaunchDescriptionSource(foo_dir + '/launch/my_launch.py'))
    
         
   
    
    object_detection_node = Node(
        package='my_yolov5_pkg',
        executable='yolo_detect',
        name = 'object_detection_node',
        remappings=[remap_camera_topic1],
                )

    ld.add_action(camera_publisher_node)
    ld.add_action(object_detection_node)
    l
    # ld.add_action(camera_publisher_node2)
    return ld