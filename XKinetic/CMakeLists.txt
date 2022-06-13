set(ENGINE_SRC_DIR ${PROJECT_SOURCE_DIR}/XKinetic)

file(GLOB_RECURSE ENGINE_SRC ${ENGINE_SRC_DIR}/*.c)

add_library(${PROJECT_NAME} SHARED ${ENGINE_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC ${ENGINE_SRC_DIR} ${PROJECT_SOURCE_DIR}/XKCore ${PROJECT_SOURCE_DIR}/XKMath ${PROJECT_SOURCE_DIR}/XKVulkan ${PROJECT_SOURCE_DIR}/XKDirectX12)
target_include_directories(${PROJECT_NAME} PUBLIC  ${PROJECT_SOURCE_DIR}/External/stb)

target_compile_definitions(${PROJECT_NAME} PUBLIC __XK_BUILD__)

target_link_libraries(${PROJECT_NAME} XKCore XKMath m)

# Check if debug build type, add compile defenition
if(CMAKE_BUILD_TYPE EQUAL "Debug")
  target_compile_definitions(${PROJECT_NAME} PUBLIC __XK_DEBUG__)
endif()
