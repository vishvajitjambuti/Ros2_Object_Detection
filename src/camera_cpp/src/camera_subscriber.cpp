// Ros2 Libraries
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"

//local libraries
#include "../include/camera_cpp/camera.h"

//openSource libraries

class CameraSubscriber : public rclcpp::Node
{
public:
    CameraSubscriber() : Node("camera_subscriber")
    {
        subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
                "image", 10, std::bind(&CameraSubscriber::imageCallback, this, std::placeholders::_1));
    }

private:
    void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg){
    try
    {
        cv::Mat image = cv::Mat(msg->height, msg->width, CV_8UC3, const_cast<unsigned char*>(msg->data.data()), msg->step);
        cv::imshow("Received Image", image);
        cv::waitKey(1);
    }
    catch (cv::Exception& e)
    {
        RCLCPP_ERROR(rclcpp::get_logger("Image subscriber"), "cv::Exception: %s", e.what());
    }
}
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CameraSubscriber>();

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}