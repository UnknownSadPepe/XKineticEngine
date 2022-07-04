cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(XKinetic VERSION 0.0.1 LANGUAGES C)

set(CMAKE_REQUIRED_FLAGS "-std=c11 -Wall -Wextra")
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_GENERATOR_PLATFORM x64)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

if(CMAKE_BUILD_TYPE EQUAL "Debug")
  set(CMAKE_REQUIRED_FLAGS CMAKE_REQUIRED_FLAGS "-g -O0")
elseif(CMAKE_BUILD_TYPE EQUAL "Release")
  set(CMAKE_REQUIRED_FLAGS CMAKE_REQUIRED_FLAGS "-O2") 
endif()

option(XKINETIC_TESTS "Build tests applications" OFF)

set(BUILD_DIR ${CMAKE_SOURCE_DIR}/Target/${CMAKE_BUILD_TYPE})
set(EXECUTABLE_OUTPUT_PATH ${BUILD_DIR})
set(LIBRARY_OUTPUT_PATH ${BUILD_DIR})

if(WIN32)
  set(CMAKE_SHADER_LIBRARY_PREFIX "")
  set(CMAKE_STATIC_LIBRARY_PREFIX "")
endif()

#add_subdirectory(XKCore)

add_subdirectory(XKMath)

if(UNIX AND NOT APPLE OR WIN64)
  add_subdirectory(XKVulkan)
endif()

if(WIN32)
  add_subdirectory(XKD3D12)
endif()

add_subdirectory(XKOpenXR)

add_subdirectory(XKinetic)

add_subdirectory(XKEditor)

if(XKINETIC_TESTS)
	add_subdirectory(Tests)
endif()
