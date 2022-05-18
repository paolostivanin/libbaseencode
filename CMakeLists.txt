cmake_minimum_required(VERSION 3.5)
project(baseencode)

include(GNUInstallDirs)

enable_testing()
add_subdirectory(tests)

# set up versioning.
set(BUILD_MAJOR "1")
set(BUILD_MINOR "0")
set(BUILD_VERSION "14")
set(BUILD_VERSION ${BUILD_MAJOR}.${BUILD_MINOR}.${BUILD_VERSION})

set(CMAKE_C_STANDARD 11)

set(BASEENCODE_HEADERS src/baseencode.h)
set(SOURCE_FILES src/base32.c src/base64.c)

set(CMAKE_C_FLAGS "-Wall -Werror -fPIC")

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${PROJECT_LIBS})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${BUILD_VERSION} SOVERSION ${BUILD_MAJOR})

set(BASEENCODE_LIB_DIR "${CMAKE_INSTALL_LIBDIR}")
set(BASEENCODE_INC_DIR "${CMAKE_INSTALL_INCLUDEDIR}")

install(
  TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${BASEENCODE_LIB_DIR}
  LIBRARY DESTINATION ${BASEENCODE_LIB_DIR}
  COMPONENT library
)

install(
  FILES ${BASEENCODE_HEADERS}
  DESTINATION ${BASEENCODE_INC_DIR}
)

# Allow adding prefix if CMAKE_INSTALL_INCLUDEDIR not absolute.
if(IS_ABSOLUTE "${CMAKE_INSTALL_INCLUDEDIR}")
    set(PKGCONFIG_TARGET_INCLUDES "${CMAKE_INSTALL_INCLUDEDIR}")
else()
    set(PKGCONFIG_TARGET_INCLUDES "\${prefix}/${CMAKE_INSTALL_INCLUDEDIR}")
endif()
# Allow adding prefix if CMAKE_INSTALL_LIBDIR not absolute.
if(IS_ABSOLUTE "${CMAKE_INSTALL_LIBDIR}")
    set(PKGCONFIG_TARGET_LIBS "${CMAKE_INSTALL_LIBDIR}")
else()
    set(PKGCONFIG_TARGET_LIBS "\${exec_prefix}/${CMAKE_INSTALL_LIBDIR}")
endif()

configure_file("baseencode.pc.in" "baseencode.pc" @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/baseencode.pc" DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig/)
