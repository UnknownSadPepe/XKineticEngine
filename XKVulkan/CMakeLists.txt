set(VULKAN_SRC_DIR ${CMAKE_SOURCE_DIR}/XKVulkan)

file(GLOB_RECURSE VULKAN_SRC ${VULKAN_SRC_DIR}/*.c)

add_library(XKVulkan SHARED ${VULKAN_SRC})

target_include_directories(XKVulkan PRIVATE ${VULKAN_SRC_DIR} ${CMAKE_SOURCE_DIR}/XKCore ${CMAKE_SOURCE_DIR}/XKMath ${CMAKE_SOURCE_DIR}/XKinetic)

target_compile_definitions(XKVulkan PRIVATE __XKVULKAN_BUILD__)

# Check if debug build type, add compile defenition
if(CMAKE_BUILD_TYPE EQUAL "Debug")
  target_compile_definitions(XKVulkan PRIVATE __XKVULKAN_DEBUG__)
endif()

find_package(Vulkan REQUIRED FATAL_ERROR)
target_link_libraries(XKVulkan Vulkan::Vulkan XKCore XKMath)
target_include_directories(XKVulkan PRIVATE ${VULKAN_INCLUDE_DIRS} $ENV{VULKAN_SDK}/include)
