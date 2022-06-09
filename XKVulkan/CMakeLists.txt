set(VULKAN_SRC_DIR ${PROJECT_SOURCE_DIR}/XKVulkan)

file(GLOB_RECURSE VULKAN_SRC ${VULKAN_SRC_DIR}/*.c)

add_library(XKVulkan SHARED ${VULKAN_SRC})

target_include_directories(XKVulkan PUBLIC ${VULKAN_SRC_DIR} ${PROJECT_SOURCE_DIR}/XKCore ${PROJECT_SOURCE_DIR}/XKMath ${PROJECT_SOURCE_DIR}/XKinetic)

find_package(Vulkan REQUIRED)
target_link_libraries(XKVulkan Vulkan::Vulkan XKCore XKMath)
target_include_directories(XKVulkan PUBLIC ${VULKAN_INCLUDE_DIRS} $ENV{VULKAN_SDK}/include)