#!/bin/sh
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 10
xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/workspace/catkin_ws/src/map/myMap4.yaml" &
sleep 5
xterm -e "rosrun add_markers pick_object_marker"&
sleep 5
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation_marker.launch" &
sleep 15 
xterm -e "rosrun pick_up pick_objects"
