# Home Service Robot 

### project done for udacity 

in this project a robot will deliver a virtual object from a instructed location and will deliver it to other instructed project 

### packages used 

##turtlebot_gazebo##
     a. for this package we use a launch file to load the turtlebot on to our world , with robot spawner manipulated such that robot is inside the world.
     b. again use another launch file to launch the ## gmapping package ## in line with turtlebot, we develop the map of our world , using another package ##turtlebot_teleop## and save the map using another package ## map_creator ##. 
     c. using the amcl.alunch file we try to lacalize the bot , for that try to match the initial positions of bot wrt map . along with ## rviz ## we use to navigate the bot to 2d nav goal position using the ##ros navigation stack move_base## with is inside ## turtlebot_navigation ##
     d. now we are devolping our  package called ## pick_up ## this package has node acting as client to ##move_base## package to sent two location to set the pick up and drop points.
     f.again we build another package to called ## add_markers## this will help to create a virtual object in the rviz using add_marker node , this is then edited to match the odom of the robot to display and hide the virtual object to sync with pick up and drop . the edited node is named pick_object_marker . 
     
 ### shell scripts 
 ####  before using the shell script , use the following tips 
     either add the following to bashrc or to source setup.bash script
     1. change the directory to match your catkin workspace 
     2. source devel/setup.bash 
 there 5 scripts  
  1. one for testing the slam 
  2. one for testing the map and navigation 
  3. one for setting the pick up package 
  4. one for setting up the virtual object hide and seek 
  5. one for setting up final home service bot . 
