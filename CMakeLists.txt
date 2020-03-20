

cmake_minimum_required(VERSION 3.0)
project(panorama)

# Set module include path
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Includes
include(FindOpenGL)
include(FindThreads)
include(GeneratePanoramaVersion)

# Set version and build date
GeneratePanoramaVersion(PANORAMA_VERSION)

# Set project properties
string(TIMESTAMP PANORAMA_BUILD_DATE "%Y-%m-%d %H:%M:%S" UTC)
set(PANORAMA_PLATFORM ${CMAKE_SYSTEM_NAME})

# Set standard
set(CMAKE_CXX_STANDARD 17)

# Find dependencies
find_package(OpenGL  REQUIRED)
find_package(SDL2    REQUIRED)
find_package(Threads REQUIRED)

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
