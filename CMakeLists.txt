cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

# Initialize XKinetic project.
project(XKinetic VERSION 0.0.1 LANGUAGES C)

# Set project build type.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

# Initialize project options.
option(BUILD_TESTS "Build tests applications" OFF)

# Set project build dir.
set(BUILD_DIR ${PROJECT_SOURCE_DIR}/Target/${CMAKE_BUILD_TYPE})
set(EXECUTABLE_OUTPUT_PATH ${BUILD_DIR})
set(LIBRARY_OUTPUT_PATH ${BUILD_DIR})

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

# Add XKinetic subdirectory.
add_subdirectory(XKinetic)

# Add XKEditor subdirectory.
add_subdirectory(XKEditor)

# Add Tests subdirectory.
if(BUILD_TESTS)
	add_subdirectory(Tests)
endif()