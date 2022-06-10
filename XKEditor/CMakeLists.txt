set(EDITOR_SRC_DIR ${PROJECT_SOURCE_DIR}/XKEditor)

file(GLOB_RECURSE EDITOR_SRC ${EDITOR_SRC_DIR}/*.c)

add_executable(XKEditor ${EDITOR_SRC})

target_include_directories(XKEditor PUBLIC ${EDITOR_SRC_DIR} ${PROJECT_SOURCE_DIR}/XKCore ${MATH_SRC_DIR} ${ENGINE_SRC_DIR})

target_link_libraries(XKEditor XKCore XKMath XKinetic)
