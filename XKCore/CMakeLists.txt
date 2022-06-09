set(CORE_SRC_DIR ${PROJECT_SOURCE_DIR}/XKCore)

file(GLOB_RECURSE CORE_SRC ${CORE_SRC_DIR}/*.c)

add_library(XKCore SHARED ${CORE_SRC})

target_include_directories(XKCore PUBLIC ${CORE_SRC_DIR})
