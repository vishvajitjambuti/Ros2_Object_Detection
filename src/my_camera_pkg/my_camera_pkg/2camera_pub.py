import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image 
from cv_bridge import CvBridge 
import cv2 
 
class ImagePublisher(Node):
	def __init__(self):
		super().__init__('two_camera_pub')
		
		self.declare_parameter('camera_id', 0)
		self.declare_parameter('camera_id_2', 2)
		self.declare_parameter('vid_stride', 60)

		self.publisher1_ = self.create_publisher(Image, 'img_1', 1)
		self.publisher2_ = self.create_publisher(Image, 'img_2', 1)
		self.get_logger().info('Camera Publisher has been started')

		timer_period_1 = 0.1  # seconds
		timer_period_2 = 0.1  # seconds
  
		self.timer_1 = timer_period_1
		self.timer_2 = timer_period_2
		# Create the timer
		self.timer_1 = self.create_timer(timer_period_1, self.timer_callback_4)
		self.timer_2 = self.create_timer(timer_period_2, self.timer_callback_2)
  
		source_1 = self.get_parameter('camera_id').value
		source_2 = self.get_parameter('camera_id_2').value
		
		self.vid_stride = self.get_parameter('vid_stride').value

		self.cap_1 = cv2.VideoCapture(source_1)
		self.cap_2 = cv2.VideoCapture(source_2)
  	
		# Used to convert between ROS and OpenCV images
		self.br = CvBridge()
	
	def timer_callback_1(self):
		print("timer_callback_1")
		
		count = 0
		success1 = True
		success2 = True
		while(success1==True) or (success2==True):
			success1, frame1 = self.cap_1.read()
			success2, frame2 = self.cap_2.read()
			if count % self.vid_stride == 0:
				# Publish the image.
				self.publisher1_.publish(self.br.cv2_to_imgmsg(frame1))
				self.publisher2_.publish(self.br.cv2_to_imgmsg(frame2))
				self.get_logger().info('Publishing image_raw_1')
				self.get_logger().info('Publishing image_raw_2')
			count += 1
		else:
			self.get_logger().info('Error reading frame')

	def timer_callback_2(self):
		print("timer_callback_2")
		
		count = 0
		success = True
		while success == True:
			success , frame = self.cap_1.read()
			if count % self.vid_stride == 0:
				self.publisher2_.publish(self.br.cv2_to_imgmsg(frame))
				self.get_logger().info('Publishing image_raw_2')
			count += 1
		else:
			self.get_logger().info('Error reading frame_2')
	
	def timer_callback_3(self):
		print("timer_callback_3")
		ret, frame = self.cap_1.read()
		if ret == True:
			self.publisher1_.publish(self.br.cv2_to_imgmsg(frame))
			self.get_logger().info('Publishing image_raw_1')
		else:
			self.get_logger().info('Error reading frame')

	def timer_callback_4(self):
		print("timer_callback_4")
		ret, frame = self.cap_2.read()
		if ret == True:
			self.publisher2_.publish(self.br.cv2_to_imgmsg(frame))
			self.get_logger().info('Publishing image_raw_2')
		else:
			self.get_logger().info('Error reading frame_2')
   
        
        
	
def main(args=None):
	rclpy.init(args=args)
	image_publisher = ImagePublisher()
	rclpy.spin(image_publisher)
	
	image_publisher.destroy_node()
	image_publisher.cap_1.release()
	image_publisher.cap_2.release()
	print('cap is released')
	rclpy.shutdown()
  
if __name__ == '__main__':
  	main()
