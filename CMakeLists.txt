cmake_minimum_required(VERSION 3.10)
project(SPH-Sim)

set(CMAKE_CXX_STANDARD 17)

# Source files
file(GLOB SRC_FILES src/*.cpp)

# Find GLFW
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

# Find OpenGL
find_package(OpenGL REQUIRED)

# ImGui source files
set(IMGUI_SRC
    src/imgui/imgui.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_tables.cpp
    src/imgui/imgui_widgets.cpp
    src/imgui/imgui_demo.cpp
    src/imgui/backends/imgui_impl_glfw.cpp
    src/imgui/backends/imgui_impl_opengl3.cpp
)

add_executable(SPH-Sim ${SRC_FILES} ${IMGUI_SRC})

target_include_directories(SPH-Sim PRIVATE
    ${GLFW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
    src/imgui
    src/imgui/backends
    src
)

target_link_libraries(SPH-Sim
    ${GLFW_LIBRARIES}
    ${OPENGL_LIBRARIES}
    dl
    pthread
)

# For Linux, you may need to link X11 and related libs
if(UNIX AND NOT APPLE)
    target_link_libraries(SPH-Sim X11 Xrandr Xi Xxf86vm Xcursor Xinerama)
endif()

add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} --build . --target clean
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)