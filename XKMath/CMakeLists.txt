set(MATH_SRC_DIR ${PROJECT_SOURCE_DIR}/XKMath)

file(GLOB_RECURSE MATH_SRC ${MATH_SRC_DIR}/*.c)

add_library(XKMath SHARED ${MATH_SRC})

target_include_directories(XKMath PUBLIC ${MATH_SRC_DIR} ${PROJECT_SOURCE_DIR}/XKCore)

target_compile_definitions(XKMath PUBLIC __XKMATH_BUILD__)

# Check if debug build type, add compile defenition
if(CMAKE_BUILD_TYPE EQUAL "Debug")
  target_compile_definitions(XKMath PUBLIC __XKMATH_DEBUG__)
endif()
