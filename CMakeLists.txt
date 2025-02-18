cmake_minimum_required(VERSION 3.15)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_BIN_DIR}/conan_toolchain.cmake")

project(imageasy)

# Include Conan dependencies
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Export compile commands for IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Handle dependencies
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/tinyfiledialogs)

# Include Conan dependencies
find_package(FFTW3 CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

# Automatically add all source files
file(GLOB_RECURSE SOURCES "src/*.cc")

# Add backend source files
file(GLOB BACKEND_SOURCES "src/backends/*.cpp")

# Add tinyfiledialogs source file
set(TINYFILEDIALOGS_SOURCE "third_party/tinyfiledialogs/tinyfiledialogs.c")

# Add stb_image implementation
set(STB_IMAGE_IMPLEMENTATION "include/stb.c")

# Add source files
add_executable(imageasy ${SOURCES} ${BACKEND_SOURCES} ${TINYFILEDIALOGS_SOURCE} ${STB_IMAGE_IMPLEMENTATION})

# Link libraries
target_link_libraries(imageasy PRIVATE FFTW3::fftw3 glad::glad glm::glm imgui::imgui glfw )
