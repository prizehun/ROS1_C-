#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
/* Your code here*/
//생성한 메세지 파일 import
#include <geometry_msgs/Vector3.h>
#include <ros_tutorials/cmd_msg.h>
/* Your code here*/


class CircularMotionPublisher
{
public:
    
    CircularMotionPublisher():loop_rate(10) //loop_rate 10Hz로 설정 
    {
        /*     Your code here       */
        /* Publisher, Subscriber 정의*/
        //ros_tutorials::cmd_msg msg;
        pub=nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 100);
        sub=nh.subscribe("/circular_motion", 100, &CircularMotionPublisher::msgCallback, this);
        /*     Your code here       */ 
    }

    /*     Your code here       */ 
    /*Subscriber의 callback 함수 설정 */  
    void msgCallback(const ros_tutorials::cmd_msg::ConstPtr& msg)
    {
        auto lin_vel = geometry_msgs::Vector3();
        lin_vel.x = msg->velocity;
        lin_vel.y = 0;
        lin_vel.z = 0;

        auto rad = msg->radius;

        auto ang_vel = geometry_msgs::Vector3();
        ang_vel.x = 0;
        ang_vel.y = 0;
        ang_vel.z = lin_vel.x / rad;

        velocity.linear = lin_vel;
        velocity.angular = ang_vel;

        ROS_INFO("Angular velocity = %f", velocity.angular.z);
    }
    /*     Your code here       */ 
    

    // loop_rate에 맞게 저장된 Twist 메시지를 Publish하도록 spin 설정 
    void spin()
    {
        while(ros::ok())
        {
            pub.publish(velocity);
            ros::spinOnce();
            loop_rate.sleep();
        }
    }

private:
    //nodehandle과 Publisher, Subscriber, 속도 정보를 저장할 Twist 메시지 객체 생성 
    ros::NodeHandle nh;
    ros::Publisher pub;
    ros::Subscriber sub;
    ros::Rate loop_rate;
    geometry_msgs::Twist velocity;
};


int main(int argc, char **argv)
{
    //ROS 시작 후 객체 생성 및 spin
    ros::init(argc, argv, "cm_publisher");
    CircularMotionPublisher cm_publisher;
    cm_publisher.spin();
    return 0;
}
