project(filter)
add_executable(filter filter.cpp)
find_package(OpenCV REQUIRED)
target_link_libraries(filter PRIVATE ${OpenCV_LIBS})