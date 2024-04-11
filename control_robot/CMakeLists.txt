cmake_minimum_required(VERSION 3.8)
project(control_robot)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(Threads REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

add_executable(control_robot src/control_robot.cpp)
ament_target_dependencies(control_robot rclcpp geometry_msgs)

add_executable(sendserialcom src/SendSerialCom.cpp)
# ament_target_dependencies(sendserialcom rclcpp)

# include_directories(sendserialcom PUBLIC 
#   include
# )

install(TARGETS
  control_robot
  sendserialcom
  DESTINATION lib/${PROJECT_NAME})
ament_package()
