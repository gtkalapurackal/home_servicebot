#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <cmath>
#include <geometry_msgs/PoseWithCovarianceStamped.h>


double pickup[2] ={2.5,2.0};
double drop[2] = {5.0,5.0};
double current_pose[2] = {0.0, 0.0};

bool reacheddrop =false;
bool reachedpick =false;
bool picked = false;
void sub_callback(const nav_msgs::Odometry::ConstPtr& msg)
{
   

  current_pose[0] = msg->pose.pose.position.x;
  current_pose[1] = msg->pose.pose.position.y;
  //ROS_INFO("Position-> x: [%f], y: [%f]",current_pose[0],current_pose[1] );
  

  double xx = pickup[0] - current_pose[0];
  double yy = pickup[1] - current_pose[1];
  double dist= sqrt ((xx*xx) + (yy*yy));
  if (dist <0.5)
  {reachedpick =true;}
  ROS_INFO("Position-> pick: [%f]",dist );
  xx = drop[0] - current_pose[0];
  yy = drop[1] - current_pose[1];
  dist= sqrt ((xx*xx) + (yy*yy));
  if( dist <0.5)
   {reacheddrop=true;}
  ROS_INFO("Position-> drop: [%f]",dist );
}
int main( int argc, char** argv )
{
  ros::init(argc, argv, "pick_object_marker");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber marker_sub = n.subscribe("odom",10,sub_callback);
  uint32_t shape = visualization_msgs::Marker::CUBE;
  
  
  while (ros::ok())
  {
    
    
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    marker.ns = "basic_shapes";
    marker.id = 0;

    marker.type = shape;

    marker.action = visualization_msgs::Marker::ADD;

    marker.pose.position.x = pickup[0];
    marker.pose.position.y = pickup[1];
    marker.pose.position.z = 0.0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    marker.scale.x = 0.25;
    marker.scale.y = 0.25;
    marker.scale.z = 0.25;

    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
     
         

      if (reachedpick)
      {
      picked = true;
      reachedpick = false;
      marker.action = visualization_msgs::Marker::DELETE;
      marker_pub.publish(marker);
      ROS_INFO("robot picked the box and going to drop  it ... ");
      }
      else if (reacheddrop)
      
     {
	
      marker.action = visualization_msgs::Marker::ADD;
      marker.pose.position.x = drop[0];
      marker.pose.position.y = drop[1];
      marker_pub.publish(marker);
      ROS_INFO("Droping the box ...");
      ROS_INFO("marker node shutting down....");
      ros::Duration(15.0).sleep();
      return 0;
      }
      else if (!picked)
     {
      marker_pub.publish(marker);
      ROS_INFO("robot comming to pick the box... ");
      }  
     ros::spinOnce(); 
  }
  
}
