set(VULKAN_TEST_SRC_DIR ${PROJECT_SOURCE_DIR}/Tests/VulkanTest)

file(GLOB_RECURSE VULKAN_TEST_SRC ${VULKAN_TEST_SRC_DIR}/*.c)

if(WIN32)
  add_executable(XKVulkanTest WIN32 ${VULKAN_TEST_SRC})
else()
  add_executable(XKVulkanTest ${VULKAN_TEST_SRC})
endif()

target_include_directories(XKVulkanTest PUBLIC ${VULKAN_TEST_SRC_DIR} ${PROJECT_SOURCE_DIR}/XKCore ${PROJECT_SOURCE_DIR}/XKMath)

target_link_libraries(XKVulkanTest XKCore XKMath XKinetic)
