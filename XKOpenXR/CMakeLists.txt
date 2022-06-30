set(OPENXR_SRC_DIR ${CMAKE_SOURCE_DIR}/XKOpenXR)

file(GLOB_RECURSE OPENXR_SRC ${OPENXR_SRC_DIR}/*.c)

add_library(XKOpenXR SHARED ${OPENXR_SRC})

target_include_directories(XKOpenXR PRIVATE ${OPENXR_SRC_DIR} ${CMAKE_SOURCE_DIR}/XKCore ${CMAKE_SOURCE_DIR}/XKMath ${CMAKE_SOURCE_DIR}/XKVulkan ${CMAKE_SOURCE_DIR}/XKDirectX12)

target_compile_definitions(XKOpenXR PRIVATE __XKOPENXR_BUILD__)

# Check if debug build type, add compile defenition
if(CMAKE_BUILD_TYPE EQUAL "Debug")
  target_compile_definitions(XKOpenXR PRIVATE __XKOPENXR_DEBUG__)
endif()

find_package(Vulkan REQUIRED FATAL_ERROR)
target_link_libraries(XKOpenXR PRIVATE XKCore XKMath)
target_include_directories(XKOpenXR PRIVATE ${VULKAN_INCLUDE_DIRS} $ENV{VULKAN_SDK}/include)
