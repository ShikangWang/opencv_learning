cmake_minimum_required(VERSION 3.1)
#set (OpenCV_DIR /home/pi/opencv/opencv-4.5.5/include)
project(read_grey)
find_package(OpenCV REQUIRED)
add_executable(read_grey read_grey.cpp)
target_link_libraries(read_grey PRIVATE ${OpenCV_LIBS})
