# Initialize XKDirectX12 project.
project(XKDirectX12 VERSION 0.0.1 LANGUAGES C CXX)

set(DIRECTX12_SRC_DIR ${CMAKE_SOURCE_DIR}/XKDirectX12)

file(GLOB_RECURSE DIRECTX12_SRC ${DIRECTX12_SRC_DIR}/*.c ${DIRECTX12_SRC_DIR}/*.cpp)

add_library(XKDirectX12 SHARED ${DIRECTX12_SRC})

target_include_directories(XKDirectX12 PRIVATE ${DIRECTX12_SRC_DIR} ${CMAKE_SOURCE_DIR}/XKCore ${CMAKE_SOURCE_DIR}/XKMath ${CMAKE_SOURCE_DIR}/XKinetic)

target_compile_definitions(XKDirectX12 PRIVATE __XKDIRECTX12_BUILD__)

target_link_libraries(XKDirectX12 PRIVATE XKCore XKMath)

target_include_directories(XKDirectX12 PRIVATE DXGI_INCLUDE_DIR)

# Check if debug build type, add compile defenition
if(CMAKE_BUILD_TYPE EQUAL "Debug")
  target_compile_definitions(XKDirectX12 PRIVATE __XKDIRECTX12_DEBUG__)
endif()

target_link_libraries(XKDirectX12 PRIVATE d3d12.lib dxgi1_6.lib)
