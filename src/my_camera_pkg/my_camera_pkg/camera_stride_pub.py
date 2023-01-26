import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image 
from cv_bridge import CvBridge 
import cv2 
from std_msgs.msg import Float64
import time
class ImagePublisher(Node):

    def __init__(self):
        super().__init__('camera_stride_pub')
        # declear paramer 
        self.declare_parameter('camera_id', 0)
        self.declare_parameter('vid_stride', 10)
        # create publisher
        self.publisher_ = self.create_publisher(Image, 'image_raw', 1)
        self.publisher2_ = self.create_publisher(Float64, 'fps', 1)
        self.get_logger().info('Camera Publisher has been started')

        # We will publish a message every 0.1 seconds
        timer_period = 0.025  # seconds
        self.timer = timer_period
        # Create the timer
        self.timer = self.create_timer(timer_period, self.timer_callback)

        # Create a get parameter

        self.source = self.get_parameter('camera_id').value
        self.vid_stride = self.get_parameter('vid_stride').value
        self.cap = cv2.VideoCapture(self.source)

        # Used to convert between ROS and OpenCV images
        self.br = CvBridge()
        

    def timer_callback(self):
        fps = Float64()
        count = 0
        success = True
        image_dims = (640, 480 )
        while success:
            success, frame = self.cap.read()            
            fps.data = self.cap.get(cv2.CAP_PROP_FPS) 
            # if ret == True:
            if count % self.vid_stride == 0:
                # rezie the frame
                resized_fram = cv2.resize(frame,  image_dims, interpolation = cv2.INTER_AREA ) 
                # Publish the image
                self.publisher_.publish(self.br.cv2_to_imgmsg(resized_fram))
                self.publisher2_.publish(fps)
                self.get_logger().info(f'Publishing {self.source} image_raw')
                # self.get_logger().info(f'height : {height}, width : {width}, channels : {channels}')
                # check the frame size 
                
            count += 1
        else:
            self.get_logger().info('Error reading frame')

    # Display the message on the console
    #self.get_logger().info('Publishing image_raw')
	
def main(args=None):
	rclpy.init(args=args)
	image_publisher = ImagePublisher()
	rclpy.spin(image_publisher)
	
	image_publisher.destroy_node()
	image_publisher.cap.release()
	print('cap is released')
	rclpy.shutdown()
  
if __name__ == '__main__':
    main()
