

# Set gl3w sources
set(GL3W_SRCS  ${PROJECT_SOURCE_DIR}/src/gl3w.c)

# Set IMGUI sources
set(IMGUI_SRCS ${PROJECT_SOURCE_DIR}/imgui/imgui.cpp
        ${PROJECT_SOURCE_DIR}/imgui/imgui_draw.cpp
        ${PROJECT_SOURCE_DIR}/imgui/imgui_widgets.cpp
        ${PROJECT_SOURCE_DIR}/imgui/imgui_impl_opengl2.cpp
        ${PROJECT_SOURCE_DIR}/imgui/imgui_impl_sdl.cpp)

# Set INIH sources
set(INIH_SRCS ${PROJECT_SOURCE_DIR}/extern/inih.c)

# Set panorama sources
set(SRCS panorama.cpp
        file_browser.cc
        PointLocalizationPane.cpp
        RosRelated.cpp
        ManageMapPane.cpp
        LoopClosurePane.cpp
        Bash.cpp
        Utils.cpp
        Sidebar.cpp
        MappingPane.cpp
        AboutDialog.cpp
        Window.cpp
        MainWindow.cpp
        Theming.cpp)

# Create the configuration file
configure_file("${PROJECT_SOURCE_DIR}/config.h.in"
        "${PROJECT_SOURCE_DIR}/include/config.h")

# Add binary target
add_executable(panorama ${GL3W_SRCS}
        ${IMGUI_SRCS}
        ${IMGUI_LIBRARIES}
        ${SRCS})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

target_include_directories(panorama PRIVATE
        ${PROJECT_SOURCE_DIR}/imgui
        ${PROJECT_SOURCE_DIR}/gl3w
        ${CMAKE_BINARY_DIR}
        ${PROJECT_SOURCE_DIR}/include
        ${SDL2_INCLUDE_DIRS}
        )

target_link_libraries(panorama Threads::Threads ${OPENGL_LIBRARIES}
        ${catkin_LIBRARIES}
        dl SDL2 cap
        stdc++fs)

# Installation
install(TARGETS panorama DESTINATION bin)
install(FILES "${PROJECT_SOURCE_DIR}/fonts/DroidSans.ttf" DESTINATION bin)
install(FILES "${PROJECT_SOURCE_DIR}/fonts/fa-solid-900.ttf" DESTINATION bin)
install(FILES ${PROJECT_SOURCE_DIR}/images/panorama.svg DESTINATION bin)

