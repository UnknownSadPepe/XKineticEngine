cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

# Initialize XKinetic project.
project(XKinetic VERSION 0.0.1 LANGUAGES C)

# Initialize project options.
option(BUILD_TESTS "Build tests applications" OFF)

# Set project build dir.
set(BUILD_DIR ${PROJECT_SOURCE_DIR}/Target)
set(EXECUTABLE_OUTPUT_PATH ${BUILD_DIR}/${CMAKE_BUILD_TYPE})
set(LIBRARY_OUTPUT_PATH ${BUILD_DIR}/${CMAKE_BUILD_TYPE})

# Add XKCore subdirectory.
add_subdirectory(XKCore)

# Add XKMath subdirectory.
add_subdirectory(XKMath)

# Add XKVulkan subdirectory.
# add_subdirectory(XKVulkan)

# Add XKDirectX12 subdirectory.
add_subdirectory(XKDirectX12)

# Add XKinetic subdirectory.
add_subdirectory(XKinetic)

# Add XKEditor subdirectory.
add_subdirectory(XKEditor)

# Add Tests subdirectory.
if(BUILD_TESTS)
	add_subdirectory(Tests)
endif()