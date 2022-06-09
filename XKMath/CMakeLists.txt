set(MATH_SRC_DIR ${PROJECT_SOURCE_DIR}/XKMath)

file(GLOB_RECURSE MATH_SRC ${MATH_SRC_DIR}/*.c)

add_library(XKMath SHARED ${MATH_SRC})

target_include_directories(XKMath PUBLIC ${MATH_SRC_DIR} ${PROJECT_SOURCE_DIR}/XKCore)
