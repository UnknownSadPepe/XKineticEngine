set(DIRECTX12_TEST_SRC_DIR ${PROJECT_SOURCE_DIR}/Tests/DirectX12Test)

file(GLOB_RECURSE DIRECTX12_TEST_SRC ${DIRECTX12_TEST_SRC_DIR}/*.c)

add_executable(XKDirectX12Test ${DIRECTX12_TEST_SRC})

target_include_directories(XKDirectX12Test PUBLIC ${DIRECTX12_TEST_SRC_DIR} ${PROJECT_SOURCE_DIR}/XKCore ${PROJECT_SOURCE_DIR}/XKMath)

target_link_libraries(XKDirectX12Test XKCore XKMath XKinetic)
