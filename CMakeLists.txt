cmake_minimum_required(VERSION 3.16)

# Set the project name
project(wave)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add an executable with the above sources
add_executable(${PROJECT_NAME} src/main.cpp src/wave.cpp src/observer.cpp src/generator.cpp)

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)