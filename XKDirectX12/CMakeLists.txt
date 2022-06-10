set(DIRECTX12_SRC_DIR ${PROJECT_SOURCE_DIR}/XKDirectX12)

file(GLOB_RECURSE DIRECTX12_SRC ${DIRECTX12_SRC_DIR}/*.c)

add_library(XKDirectX12 SHARED ${DIRECTX12_SRC})

target_include_directories(XKDirectX12 PUBLIC ${DIRECTX12_SRC_DIR} ${PROJECT_SOURCE_DIR}/XKCore ${PROJECT_SOURCE_DIR}/XKMath ${PROJECT_SOURCE_DIR}/XKinetic)

target_compile_definitions(XKDirectX12 PUBLIC __XKDIRECTX12_BUILD__)

target_link_libraries(XKDirectX12 XKCore XKMath)

# Check if debug build type, add compile defenition
if(CMAKE_BUILD_TYPE EQUAL "Debug")
  target_compile_definitions(XKDirectX12 PUBLIC __XKDIRECTX12_DEBUG__)
endif()
