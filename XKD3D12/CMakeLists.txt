set(D3D12_SRC_DIR ${CMAKE_SOURCE_DIR}/XKD3D12)

file(GLOB_RECURSE D3D12_SRC ${D3D12_SRC_DIR}/*.c)

add_library(XKDirectX12 SHARED ${D3D12_SRC})

target_include_directories(XKDirectX12 PRIVATE ${D3D12_SRC_DIR} ${CMAKE_SOURCE_DIR}/XKCore ${CMAKE_SOURCE_DIR}/XKMath ${CMAKE_SOURCE_DIR}/XKinetic)

target_compile_definitions(XKDirectX12 PRIVATE __XKD3D12_BUILD__)

target_link_libraries(XKDirectX12 PRIVATE XKCore XKMath)

target_include_directories(XKDirectX12 PRIVATE DXGI_INCLUDE_DIR)

# Check if debug build type, add compile defenition
if(CMAKE_BUILD_TYPE EQUAL "Debug")
  target_compile_definitions(XKDirectX12 PRIVATE __XKD3D12_DEBUG__)
endif()

target_link_libraries(XKDirectX12 PRIVATE d3d12.lib dxgi.lib dxguid.lib d3dcompiler)
