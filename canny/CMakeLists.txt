project(canny)
add_executable(canny canny.cpp)
find_package(OpenCV REQUIRED)
target_link_libraries(canny PRIVATE ${OpenCV_LIBS})