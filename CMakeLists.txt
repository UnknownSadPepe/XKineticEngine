cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

# Initialize XKinetic project.
project(XKinetic VERSION 0.0.1 LANGUAGES C)

# Set project C standard.
set(CMAKE_REQUIRED_FLAGS "-std=c2x -Wall -Wextra")
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_GENERATOR_PLATFORM x64)

# Set project build type.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

if(CMAKE_BUILD_TYPE EQUAL "Debug")
  set(CMAKE_REQUIRED_FLAGS CMAKE_REQUIRED_FLAGS "-g -O0")
elseif(CMAKE_BUILD_TYPE EQUAL "Release")
  set(CMAKE_REQUIRED_FLAGS CMAKE_REQUIRED_FLAGS "-O2") 
endif()

# Initialize project options.
option(XKINETIC_TESTS "Build tests applications" OFF)

# Set project build dir.
set(BUILD_DIR ${CMAKE_SOURCE_DIR}/Target/${CMAKE_BUILD_TYPE})
set(EXECUTABLE_OUTPUT_PATH ${BUILD_DIR})
set(LIBRARY_OUTPUT_PATH ${BUILD_DIR})

# Remove all libraries prefix
if(WIN32)
  set(CMAKE_SHADER_LIBRARY_PREFIX "")
  set(CMAKE_STATIC_LIBRARY_PREFIX "")
endif()

# Add XKCore subdirectory.
add_subdirectory(XKCore)

# Add XKMath subdirectory.
add_subdirectory(XKMath)

# Add XKVulkan subdirectory.
if(UNIX AND NOT APPLE OR WIN32)
  add_subdirectory(XKVulkan)
endif()

# Add XKDirectX12 subdirectory.
if(WIN32)
  add_subdirectory(XKDirectX12)
endif()

# Add XKOpenXR subdirectory.
add_subdirectory(XKOpenXR)

# Add XKinetic subdirectory.
add_subdirectory(XKinetic)

# Add XKEditor subdirectory.
add_subdirectory(XKEditor)

# Add Tests subdirectory.
if(XKINETIC_TESTS)
	add_subdirectory(Tests)
endif()
