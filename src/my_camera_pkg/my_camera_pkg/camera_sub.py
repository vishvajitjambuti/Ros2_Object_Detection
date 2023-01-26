import rclpy 
from rclpy.node import Node 
from sensor_msgs.msg import Image 
from cv_bridge import CvBridge 
import cv2 
import time 
from std_msgs.msg import Float64


class ImageSubscriber(Node):
    
	"""
	Create an ImageSubscriber class, which is a subclass of the Node class.
	"""
	def __init__(self):
		"""
		Class constructor to set up the node
		"""
		super().__init__('camera_sub')
		self.declare_parameter('window_name', 'camera')
		
	
		self.subscription = self.create_subscription(Image, 'image_raw', self.listener_callback, 1)													
		self.subscription2 = self.create_subscription(Float64, 'fps', self.cb, 1)
		self.get_logger().info('Camera Subscriber has been started')
		self.subscription # prevent unused variable warning
		self.subscription2
		self.br = CvBridge()
		self.prev_frame_time = 0
		self.new_frame_time = 0
		self.window_name = self.get_parameter('window_name').value
	def listener_callback(self, data):
		"""
		Callback function.
		"""
		
		#self.get_logger().info('Receiving image_raw')
		
		# Convert ROS Image message to OpenCV image
		current_frame = self.br.imgmsg_to_cv2(data)
		# Display image
		cv2.imshow(f"{self.window_name}", current_frame)

		if cv2.waitKey(1) & 0xFF == ord('q'):
			cv2.destroyAllWindows()
			
	def cb(self, fps):
		#self.get_logger().info('Receiving fps')
		print(f"frame rate  read by camera : {fps.data}")


def main(args=None):
	rclpy.init(args=args)
	image_subscriber = ImageSubscriber()
	rclpy.spin(image_subscriber)
	image_subscriber.destroy_node()
	rclpy.shutdown()
  
if __name__ == '__main__':
    main()
