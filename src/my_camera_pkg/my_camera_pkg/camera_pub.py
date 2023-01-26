import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image 
from cv_bridge import CvBridge 
import cv2 
from std_msgs.msg import Float64
import time

class ImagePublisher(Node):
	"""
	Create an ImagePublisher class, which is a subclass of the Node class.
	"""
	def __init__(self):		
		"""
		Class constructor to set up the node
		"""

		super().__init__('camera_pub')
		
		self.declare_parameter('camera_id', 0)

		# Create the publisher. This publisher will publish an Image
		# to the video_frames topic. The queue size is 10 messages.
		self.publisher_ = self.create_publisher(Image, 'image_raw', 1)
		self.publisher2_ = self.create_publisher(Float64, 'fps', 1)
		self.get_logger().info('Camera Publisher has been started')

		# We will publish a message every 0.1 seconds
		timer_period = 0.025  # seconds
		self.timer = timer_period
		# Create the timer
		self.timer = self.create_timer(timer_period, self.timer_callback)
			
		# Create a VideoCapture object

		source = self.get_parameter('camera_id').value
		self.cap = cv2.VideoCapture(source)
			
		# Used to convert between ROS and OpenCV images
		self.br = CvBridge()
	
	def timer_callback(self):
		fps = Float64()
		# Capture frame-by-frame
		ret, frame = self.cap.read()
		fps.data = self.cap.get(cv2.CAP_PROP_FPS)
		self.publisher2_.publish(fps)
			
		if ret == True:
			#time.sleep(4* self.timer)
			# Publish the image
			self.publisher_.publish(self.br.cv2_to_imgmsg(frame))
			self.get_logger().info('Publishing image_raw')
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
