#include <ros/ros.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/Twist.h>

class SubscribeAndPublish  
{  
public:  
    SubscribeAndPublish()  
    {  
    //Topic you want to publish  
    pub_ = n_.advertise<geometry_msgs::Twist>("/cmd_vel", 10);  
    
    //Topic you want to subscribe  
    sub_ = n_.subscribe ("/cmu_cmd_vel", 10, &SubscribeAndPublish::callback, this);  //注意这里，和平时使用回调函数不一样了。
    }  
    
    void callback(const geometry_msgs::TwistStamped& cmu_cmd_vel)  
    {  
        geometry_msgs::Twist cmd_vel;  
        //.... do something with the input and generate the output...  
        cmd_vel.linear.x =cmu_cmd_vel.twist.linear.x;
        cmd_vel.linear.y =cmu_cmd_vel.twist.linear.y;
        cmd_vel.linear.z =cmu_cmd_vel.twist.linear.z;

        cmd_vel.angular.x = cmu_cmd_vel.twist.angular.x;
        cmd_vel.angular.y = cmu_cmd_vel.twist.angular.y;
        cmd_vel.angular.z = cmu_cmd_vel.twist.angular.z;
        // if(cmu_cmd_vel.twist.angular.z != 0){
        //     ROS_INFO("cmu_cmd_vel.z 的值：%f \n", cmu_cmd_vel.twist.angular.z);
        // }
        pub_.publish(cmd_vel);  
    }  
    
private:  
    ros::NodeHandle n_;   
    ros::Publisher pub_;  
    ros::Subscriber sub_;  
    
};//End of class SubscribeAndPublish  
    
int main(int argc, char **argv)  
{  
    //Initiate ROS  
    ros::init(argc, argv, "remapTwist");  
    
    //Create an object of class SubscribeAndPublish that will take care of everything  
    SubscribeAndPublish remapTwist_Object;  
    
    ros::spin();  
    
    return 0;  
} 
