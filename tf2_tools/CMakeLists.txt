cmake_minimum_required(VERSION 2.8.3)
project(tf2_tools)

find_package(catkin REQUIRED COMPONENTS tf2
                                         tf2_msgs
                                         tf2_ros
)

catkin_package(
   CATKIN_DEPENDS tf2
                  tf2_msgs
                  tf2_ros)


install(FILES scripts/view_frames.py
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
