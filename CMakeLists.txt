cmake_minimum_required(VERSION 3.25.1)

project(opengl)

file(GLOB helloworld_SRC "src/*.cpp")

add_executable(opengl ${helloworld_SRC})
target_link_libraries(opengl glfw dl pthread X11  Xrandr Xi)

include_directories(opengl PRIVATE includes)

# glad
add_subdirectory(libs/deps)
target_link_libraries(opengl deps)

# primitives
add_subdirectory(libs/primitives)
target_link_libraries(opengl primitives)

#operations
add_subdirectory(libs/math)
target_link_libraries(opengl math)
