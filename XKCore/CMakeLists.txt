set(CORE_SRC_DIR ${PROJECT_SOURCE_DIR}/XKCore)

file(GLOB_RECURSE CORE_SRC ${CORE_SRC_DIR}/*.c)

add_library(XKCore SHARED ${CORE_SRC})

target_include_directories(XKCore PUBLIC ${CORE_SRC_DIR})

target_compile_definitions(XKCore PUBLIC __XKCORE_BUILD__)

# Check if debug build type, add compile defenition
if(CMAKE_BUILD_TYPE EQUAL "Debug")
  target_compile_definitions(XKCore PUBLIC __XKCORE_DEBUG__)
endif()

# Generate Wayland headers.
if(UNIX AND NOT APPLE)
  find_program(WAYLAND_SCANNER_EXECUTABLE NAMES wayland-scanner)

  include(FindPkgConfig)
	pkg_check_modules(Wayland REQUIRED wayland-client>=0.2.7 wayland-protocols>=1.15 wayland-cursor>=0.2.7 xkbcommon>=0.5.0)
	target_include_directories(XKCore PUBLIC ${Wayland_INCLUDE_DIRS})

  pkg_get_variable(WAYLAND_PROTOCOLS_BASE wayland-protocols pkgdatadir)
  pkg_get_variable(WAYLAND_CLIENT_PKGDATADIR wayland-client pkgdatadir)

  macro(wayland_generate protocol_file output_file)
    add_custom_command(OUTPUT "${output_file}.h"
      COMMAND "${WAYLAND_SCANNER_EXECUTABLE}" client-header "${protocol_file}" "${output_file}.h"
      DEPENDS "${protocol_file}"
      VERBATIM)

    add_custom_command(OUTPUT "${output_file}-code.h"
      COMMAND "${WAYLAND_SCANNER_EXECUTABLE}" private-code "${protocol_file}" "${output_file}-code.h"
      DEPENDS "${protocol_file}"
      VERBATIM)

		target_sources(XKCore PUBLIC "${output_file}.h" "${output_file}-code.h")
  endmacro()

  wayland_generate(
    "${WAYLAND_CLIENT_PKGDATADIR}/wayland.xml"
    "${CORE_SRC_DIR}/XKinetic/Platform/Linux/wayland-client-protocol")

  wayland_generate(
    "${WAYLAND_PROTOCOLS_BASE}/stable/xdg-shell/xdg-shell.xml"
    "${CORE_SRC_DIR}/XKinetic/Platform/Linux/wayland-xdg-shell-client-protocol")

  wayland_generate(
    "${WAYLAND_PROTOCOLS_BASE}/unstable/xdg-decoration/xdg-decoration-unstable-v1.xml"
    "${CORE_SRC_DIR}/XKinetic/Platform/Linux/wayland-xdg-decoration-client-protocol")

  wayland_generate(
    "${WAYLAND_PROTOCOLS_BASE}/stable/viewporter/viewporter.xml"
    "${CORE_SRC_DIR}/XKinetic/Platform/Linux/wayland-viewporter-client-protocol")

  wayland_generate(
    "${WAYLAND_PROTOCOLS_BASE}/unstable/relative-pointer/relative-pointer-unstable-v1.xml"
    "${CORE_SRC_DIR}/XKinetic/Platform/Linux/wayland-relative-pointer-unstable-v1-client-protocol")

  wayland_generate(
    "${WAYLAND_PROTOCOLS_BASE}/unstable/pointer-constraints/pointer-constraints-unstable-v1.xml"
    "${CORE_SRC_DIR}/XKinetic/Platform/Linux/wayland-pointer-constraints-unstable-v1-client-protocol")

  wayland_generate(
    "${WAYLAND_PROTOCOLS_BASE}/unstable/idle-inhibit/idle-inhibit-unstable-v1.xml"
    "${CORE_SRC_DIR}/XKinetic/Platform/Linux/wayland-idle-inhibit-unstable-v1-client-protocol")

	target_link_libraries(XKCore PUBLIC wayland-client wayland-cursor wayland-egl xkbcommon)
endif()

# Link Unix specific libraries.
if(UNIX AND NOT APPLE)
  target_link_libraries(XKCore PRIVATE dl rt)
endif()