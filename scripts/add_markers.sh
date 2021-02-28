#!/bin/sh
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 10
xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/workspace/catkin_ws/src/map/myMap4.yaml" &
sleep 5
xterm -e "rosrun add_markers add_markers"&
sleep 3
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" 


