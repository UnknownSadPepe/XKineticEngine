set(VULKAN_TEST_SRC_DIR ${PROJECT_SOURCE_DIR}/Tests/VulkanTest)

file(GLOB_RECURSE VULKAN_TEST_SRC ${VULKAN_TEST_SRC_DIR}/*.c)

if(WIN32)
  add_executable(XKVulkanTest WIN32 ${VULKAN_TEST_SRC})
else()
  add_executable(XKVulkanTest ${VULKAN_TEST_SRC})
endif()

target_include_directories(XKVulkanTest PRIVATE ${VULKAN_TEST_SRC_DIR} ${PROJECT_SOURCE_DIR}/XKCore ${PROJECT_SOURCE_DIR}/XKMath ${PROJECT_SOURCE_DIR}/XKinetic)

target_link_libraries(XKVulkanTest PRIVATE XKCore XKMath XKinetic)
