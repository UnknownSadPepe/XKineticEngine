set(EDITOR_SRC_DIR ${PROJECT_SOURCE_DIR}/XKEditor)

file(GLOB_RECURSE EDITOR_SRC ${EDITOR_SRC_DIR}/*.c)

if(WIN32)
  add_executable(XKEditor WIN32 ${EDITOR_SRC})
else()
  add_executable(XKEditor ${EDITOR_SRC})
endif()

target_include_directories(XKEditor PUBLIC ${EDITOR_SRC_DIR} ${PROJECT_SOURCE_DIR}/XKCore ${PROJECT_SOURCE_DIR}/XKMath ${PROJECT_SOURCE_DIR}/XKinetic)

target_link_libraries(XKEditor XKCore XKMath XKinetic)
