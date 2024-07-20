cmake_minimum_required(VERSION 3.25.1)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")
project(opengl)

file(GLOB helloworld_SRC "src/*.cpp")

add_executable(opengl ${helloworld_SRC})
target_link_libraries(opengl glfw dl pthread X11  Xrandr Xi assimp)

include_directories(opengl PRIVATE includes)
include_directories(opengl PRIVATE includes/deps)

# glad
add_subdirectory(libs/deps)
target_link_libraries(opengl deps)

#objects
add_subdirectory(libs/objects)
target_link_libraries(opengl objects)

# models
add_subdirectory(libs/model)
target_link_libraries(opengl model)

# primitives
add_subdirectory(libs/primitives)
target_link_libraries(opengl primitives)

#operations
add_subdirectory(libs/math)
target_link_libraries(opengl math)

