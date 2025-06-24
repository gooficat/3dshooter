cmake_minimum_required(VERSION 3.10)
project(FPSGame)

# Find GLFW package
find_package(glfw3 REQUIRED)

# Find OpenGL package
find_package(OpenGL REQUIRED)

# Add include directories
include_directories(include)

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c")

# Add executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Link GLFW and OpenGL libraries
target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL)
