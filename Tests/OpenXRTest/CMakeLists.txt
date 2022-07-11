set(OPENXR_TEST_SRC_DIR ${PROJECT_SOURCE_DIR}/Tests/OpenXRTest)

file(GLOB_RECURSE OPENXR_TEST_SRC ${OPENXR_TEST_SRC_DIR}/*.c)

if(WIN32)
	add_executable(XKOpenXRTest WIN32 ${OPENXR_TEST_SRC})
else()
  add_executable(XKOpenXRTest ${OPENXR_TEST_SRC})
endif()

target_include_directories(XKOpenXRTest PRIVATE ${OPENXR_TEST_SRC_DIR} ${PROJECT_SOURCE_DIR}/XKCore ${PROJECT_SOURCE_DIR}/XKMath ${PROJECT_SOURCE_DIR}/XKinetic)

target_link_libraries(XKOpenXRTest PRIVATE XKCore XKMath XKinetic)
