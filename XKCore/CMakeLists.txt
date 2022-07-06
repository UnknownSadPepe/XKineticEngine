set(CORE_SRC_DIR ${PROJECT_SOURCE_DIR}/XKCore)

file(GLOB PLATFOMR_SRC ${CORE_SRC_DIR}/XKinetic/Platform/*.c)



file(GLOB_RECURSE CORE_SRC ${CORE_SRC_DIR}/XKinetic/Core/*.c)

add_library(XKCore SHARED ${CORE_SRC} ${PLATFOMR_SRC})

if(UNIX OR APPLE)
  # Posix/Unix system.
  file(GLOB POSIX_SRC ${CORE_SRC_DIR}/XKinetic/Platform/Posix/*.c)
  target_sources(XKCore PRIVATE ${POSIX_SRC})

  file(GLOB UNIX_SRC ${CORE_SRC_DIR}/XKinetic/Platform/Unix/*.c)
  target_sources(XKCore PRIVATE ${UNIX_SRC})
endif()

if(UNIX AND NOT APPLE)
  # Linux system.
  file(GLOB LINUX_SRC ${CORE_SRC_DIR}/XKinetic/Platform/Linux/*.c)
  target_sources(XKCore PRIVATE ${LINUX_SRC})
elseif(APPLE)
  # Apple system.
  file(GLOB UNIX_SRC ${CORE_SRC_DIR}/XKinetic/Platform/Cocoa/*.m)
  target_sources(XKCore PRIVATE ${UNIX_SRC})
elseif(WIN32)
  # Windows system.
  file(GLOB WIN32_SRC ${CORE_SRC_DIR}/XKinetic/Platform/Win32/*.c)
	target_sources(XKCore PRIVATE ${WIN32_SRC})
endif()

target_include_directories(XKCore PRIVATE ${CORE_SRC_DIR})

if(WIN32)
	target_include_directories(XKCore PRIVATE  ${PROJECT_SOURCE_DIR}/External/mingw)
endif()

if(UNIX AND NOT APPLE)
	target_include_directories(XKCore PRIVATE  ${PROJECT_SOURCE_DIR}/External/wayland)
endif()

target_compile_definitions(XKCore PRIVATE __XKCORE_BUILD__)

if(CMAKE_BUILD_TYPE EQUAL "Debug")
  target_compile_definitions(XKCore PUBLIC __XKCORE_DEBUG__)
endif()

# Generate Wayland headers.
if(UNIX AND NOT APPLE)
  find_program(WAYLAND_SCANNER_EXECUTABLE NAMES wayland-scanner)

  include(FindPkgConfig)
	pkg_check_modules(Wayland REQUIRED wayland-client>=0.2.7 wayland-protocols>=1.15 wayland-cursor>=0.2.7 xkbcommon>=0.5.0)
	target_include_directories(XKCore PRIVATE ${Wayland_INCLUDE_DIRS})

  pkg_get_variable(WAYLAND_PROTOCOLS_BASE wayland-protocols pkgdatadir)
  pkg_get_variable(WAYLAND_CLIENT_PKGDATADIR wayland-client pkgdatadir)

  macro(wayland_generate protocol_file output_file)
    add_custom_command(OUTPUT "${output_file}.h"
      COMMAND "${WAYLAND_SCANNER_EXECUTABLE}" -c client-header "${protocol_file}" "${output_file}.h"
      DEPENDS "${protocol_file}"
      VERBATIM)

    add_custom_command(OUTPUT "${output_file}-code.h"
      COMMAND "${WAYLAND_SCANNER_EXECUTABLE}" -c private-code "${protocol_file}" "${output_file}-code.h"
      DEPENDS "${protocol_file}"
      VERBATIM)

		target_sources(XKCore PRIVATE "${output_file}.h" "${output_file}-code.h")
  endmacro()

  wayland_generate(
    "${WAYLAND_CLIENT_PKGDATADIR}/wayland.xml"
		"${PROJECT_SOURCE_DIR}/External/wayland/wayland-client-protocol")

  wayland_generate(
    "${WAYLAND_PROTOCOLS_BASE}/stable/xdg-shell/xdg-shell.xml"
		"${PROJECT_SOURCE_DIR}/External/wayland/xdg-shell-client-protocol")

  wayland_generate(
    "${WAYLAND_PROTOCOLS_BASE}/unstable/xdg-decoration/xdg-decoration-unstable-v1.xml"
		"${PROJECT_SOURCE_DIR}/External/wayland/xdg-decoration-client-protocol")

  wayland_generate(
    "${WAYLAND_PROTOCOLS_BASE}/unstable/relative-pointer/relative-pointer-unstable-v1.xml"
		"${PROJECT_SOURCE_DIR}/External/wayland/wayland-relative-pointer-unstable-v1-client-protocol")

  wayland_generate(
    "${WAYLAND_PROTOCOLS_BASE}/unstable/pointer-constraints/pointer-constraints-unstable-v1.xml"
		"${PROJECT_SOURCE_DIR}/External/wayland/wayland-pointer-constraints-unstable-v1-client-protocol")

  wayland_generate(
    "${WAYLAND_PROTOCOLS_BASE}/unstable/idle-inhibit/idle-inhibit-unstable-v1.xml"
		"${PROJECT_SOURCE_DIR}/External/wayland/wayland-idle-inhibit-unstable-v1-client-protocol")

	target_link_libraries(XKCore PRIVATE wayland-client wayland-cursor xkbcommon)
endif()

if(WIN32)
  target_link_libraries(XKCore PRIVATE user32 gdi32)   
endif()

if(UNIX AND NOT APPLE)
  target_link_libraries(XKCore PRIVATE dl rt pthread)
endif()
