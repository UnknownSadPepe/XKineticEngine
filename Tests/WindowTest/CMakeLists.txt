set(WINDOW_TEST_SRC_DIR ${PROJECT_SOURCE_DIR}/Tests/WindowTest)

file(GLOB_RECURSE WINDOW_TEST_SRC ${WINDOW_TEST_SRC_DIR}/*.c)

if(WIN32)
  add_executable(XKWindowTest WIN32 ${WINDOW_TEST_SRC})
else()
  add_executable(XKWindowTest ${WINDOW_TEST_SRC})
endif()

target_include_directories(XKWindowTest PRIVATE ${WINDOW_TEST_SRC_DIR} ${PROJECT_SOURCE_DIR}/XKCore ${PROJECT_SOURCE_DIR}/XKinetic)

target_link_libraries(XKWindowTest PRIVATE XKCore XKinetic)
