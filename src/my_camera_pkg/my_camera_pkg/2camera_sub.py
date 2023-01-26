
import rclpy 
from rclpy.node import Node 
from sensor_msgs.msg import Image 

from cv_bridge import CvBridge 
import cv2 
 



class ImageSubscriber(Node):

    def __init__(self):

        super().__init__('two_camera_sub')
        self.subscription_1 = self.create_subscription(Image,  'img_1', self.listener_callback_1,  1)
        # self.subscription_2 = self.create_subscription(Image,  'img_2', lambda:self.listener_callback_1('src_2', Image), 10)
        self.subscription_2 = self.create_subscription(Image,  'img_2', self.listener_callback_2, 1)
        
        # self.subscription_1 = self.create_subscription(Image,  ["src_1",'img_1'], self.listener_callback_1,  10)
        self.get_logger().info('Camera Subscriber has been started')
        
        self.subscription_1 # prevent unused variable warning
        self.subscription_2
        self.br = CvBridge()
        # img1 = self.br.imgmsg_to_cv2(self.img[0])
        # print(f'img1: {img1.shape}')
        

    def listener_callback_1(self,  data ):		
        self.get_logger().info('Receiving img_1')
        current_frame = self.br.imgmsg_to_cv2(data)
        cv2.imshow(f"camera_1", current_frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            cv2.destroyAllWindows()

    def listener_callback_2(self, data):
        self.get_logger().info('Receiving img_2')
        current_frame = self.br.imgmsg_to_cv2(data)
        cv2.imshow("camera_2", current_frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            cv2.destroyAllWindows()
  
def main(args=None):
    rclpy.init(args=args)
    image_subscriber = ImageSubscriber()
   
    rclpy.spin(image_subscriber)
    image_subscriber.destroy_node()
    rclpy.shutdown()
  
if __name__ == '__main__':
    main()
