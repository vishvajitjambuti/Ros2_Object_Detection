// Ros2 Libraries
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"

//local libraries
#include "../include/camera_cpp/camera.h"
#include "../../submodule/filereaderwriter/include/fileReaderWriter.h"

//openSource libraries


class CameraNode : public rclcpp::Node
{
public:
    CameraNode() : Node("camera_publisher")
    {
        this->declare_parameter("name", "CameraFront");
        cam.name=this->get_parameter("name").get_parameter_value().get<std::string>();
        cam.initializeCamera();
        cam.openCamera();
        RCLCPP_INFO(this->get_logger(), "Connected with Camera %s", cam.name.c_str());

        publisher_ = this->create_publisher<sensor_msgs::msg::Image>("image", 10);
        timer_ = this->create_wall_timer(std::chrono::milliseconds(100),
                                         std::bind(&CameraNode::publishImage, this));
        RCLCPP_INFO(this->get_logger(), "Publish Image");
    }

private:
    Camera cam;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;

    void publishImage()
    {
        cam.getImage(imagetype_undistorted);
        auto msg = sensor_msgs::msg::Image();
        cv::resize(cam.imageLiveUndistorted, cam.imageLiveUndistorted, cv::Size( 640, 480));
        msg.data = std::vector<uint8_t>(cam.imageLiveUndistorted.data, cam.imageLiveUndistorted.data + cam.imageLiveUndistorted.total() * cam.imageLiveUndistorted.elemSize());
        msg.height = cam.imageLiveUndistorted.rows;
        msg.width = cam.imageLiveUndistorted.cols;
        msg.encoding = "bgr8";
        msg.step = cam.imageLiveUndistorted.step;
        publisher_->publish(msg);
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CameraNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
