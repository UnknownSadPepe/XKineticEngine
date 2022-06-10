set(CORE_SRC_DIR ${PROJECT_SOURCE_DIR}/XKCore)

file(GLOB_RECURSE CORE_SRC ${PROJECT_SOURCE_DIR}/XKCore/*.c)

add_library(XKCore SHARED ${CORE_SRC})

target_include_directories(XKCore PUBLIC ${CORE_SRC_DIR})

target_compile_definitions(XKCore PUBLIC __XKCORE_BUILD__)

# Check if debug build type, add compile defenition
if(CMAKE_BUILD_TYPE EQUAL "Debug")
  target_compile_definitions(XKCore PUBLIC __XKCORE_DEBUG__)
endif()
