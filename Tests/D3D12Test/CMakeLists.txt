set(D3D12_TEST_SRC_DIR ${PROJECT_SOURCE_DIR}/Tests/D3D12Test)

file(GLOB_RECURSE D3D12_TEST_SRC ${D3D12_TEST_SRC_DIR}/*.c)

if(WIN32)
  add_executable(XKD3D12Test WIN32 ${D3D12_TEST_SRC})
else()
  add_executable(XKD3D12Test ${D3D12_TEST_SRC})
endif()

target_include_directories(XKD3D12Test PRIVATE ${D3D12_TEST_SRC_DIR} ${PROJECT_SOURCE_DIR}/XKCore ${PROJECT_SOURCE_DIR}/XKMath ${PROJECT_SOURCE_DIR}/XKinetic)

target_link_libraries(XKD3D12Test PRIVATE XKCore XKMath XKinetic)
