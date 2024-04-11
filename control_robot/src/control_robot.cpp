#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <string>
#include <memory>
#include <chrono>
#include <functional>

#include "SerialCom.cpp"

using namespace std;
using namespace std::chrono_literals;
using std::placeholders::_1;

class Control_robot : public rclcpp::Node
{
public:
    Control_robot() : rclcpp::Node("Control_robot")
    {
        subscription_cmd = this->create_subscription<geometry_msgs::msg::Twist>("/cmd_vel", 10, std::bind(&Control_robot::sub_callback, this, std::placeholders::_1));
        sp1.init("/dev/ttyCH341USB0",115200);
    }

private:
    void sub_callback(const geometry_msgs::msg::Twist _cmd) const
    {
        RCLCPP_INFO(this->get_logger(),"linear:  %f",_cmd.linear.x);
        RCLCPP_INFO(this->get_logger(),"angular: %f",_cmd.angular.z);
        const_cast<SerialPort&>(sp1).write((_cmd.linear.x+0.26),(_cmd.angular.z+1.0),0,0,0);
        usleep(100000);
    }
    SerialPort sp1;
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_cmd;
};

int main(int argc,char **argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<Control_robot>();
    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(node);
    executor.spin();
    rclcpp::shutdown();    
    return 0;
}
