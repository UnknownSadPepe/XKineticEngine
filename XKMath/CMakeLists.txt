set(MATH_SRC_DIR ${PROJECT_SOURCE_DIR}/XKMath)

file(GLOB_RECURSE MATH_SRC ${MATH_SRC_DIR}/*.c)

add_library(XKMath SHARED ${MATH_SRC})

target_include_directories(XKMath PRIVATE ${MATH_SRC_DIR} ${PROJECT_SOURCE_DIR}/XKCore)

target_compile_definitions(XKMath PRIVATE __XKMATH_BUILD__)

# Initialize project options.
option(XKMATH_AVX "Build AVX instructions" OFF)
option(XKMATH_AVX2 "Build AVX2 instructions" ON)

if(XMATH_AVX)
	target_compile_options(XKMath PUBLIC -mavx)
	target_compile_definitions(XKMath PUBLIC __XKMATH_AVX__)
elseif(XKMATH_AVX2)
	target_compile_options(XKMath PUBLIC -mavx2)
	target_compile_definitions(XKMath PUBLIC __XKMATH_AVX2__)
endif()

# Check if debug build type, add compile defenition
if(CMAKE_BUILD_TYPE EQUAL "Debug")
  target_compile_definitions(XKMath PRIVATE __XKMATH_DEBUG__)
endif()
