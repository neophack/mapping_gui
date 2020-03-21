

cmake_minimum_required(VERSION 3.0)
project(panorama)
include_directories(${PROJECT_BINARY_DIR})
# Set module include path
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
if(UNIX)
    if (APPLE)
        add_definitions(-DAPPLE)
    else()
        add_definitions(-DLINUX)
    endif()
    add_definitions(-DUNIX)
elseif(WIN32)
    add_definitions(-DWIN32)
    add_definitions(-DMINGW32)
    set(DIRENT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/3rdparty/dirent/include)
    include_directories(${DIRENT_INCLUDE_DIR})
endif()
if(MSVC)
    add_definitions(-DMSVC)
endif()
# Includes
include(FindOpenGL)
include(FindThreads)
include(GeneratePanoramaVersion)

# Set version and build date

# Set project properties
string(TIMESTAMP PANORAMA_BUILD_DATE "%Y-%m-%d %H:%M:%S" UTC)
set(PANORAMA_PLATFORM ${CMAKE_SYSTEM_NAME})
set(PANORAMA_VERSION "1.0.0")

# Set standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

# Find dependencies
find_package(catkin REQUIRED COMPONENTS
        rospy
        roscpp
        std_msgs
        nav_msgs
        sensor_msgs
        cv_bridge
        tf
        tf2
        tf2_ros
        eigen_conversions
        message_filters
        roslib
        pcl_ros
        )

find_package(OpenGL  REQUIRED)
find_package(SDL2    REQUIRED)
find_package(Threads REQUIRED)
include_directories(
        include
        ${Boost_INCLUDE_DIRS}
        ${catkin_INCLUDE_DIRS}
)
# Generate GL3W headers using the provided script
message("Downloading gl3w sources into Panorama source tree...")
execute_process(COMMAND "python" "${CMAKE_SOURCE_DIR}/gl3w/gl3w_gen.py" "--ext" "--root=.."
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/gl3w")

# Uninstall target
configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

# Add subfolders
add_subdirectory(src)
