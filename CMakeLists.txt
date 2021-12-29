cmake_minimum_required(VERSION 3.5)
project(baseencode)

enable_testing()
add_subdirectory(tests)

# set up versioning.
set(BUILD_MAJOR "1")
set(BUILD_MINOR "0")
set(BUILD_VERSION "12")
set(BUILD_VERSION ${BUILD_MAJOR}.${BUILD_MINOR}.${BUILD_VERSION})

set(CMAKE_C_STANDARD 11)

set(BASEENCODE_HEADERS src/baseencode.h)
set(SOURCE_FILES src/base32.c src/base64.c)

set(CMAKE_C_FLAGS "-Wall -Werror -fPIC")

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${PROJECT_LIBS})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${BUILD_VERSION} SOVERSION ${BUILD_MAJOR})

include(GNUInstallDirs)
set(LIB_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}") # "lib" or "lib64"

install(
  TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
  LIBRARY DESTINATION ${LIB_INSTALL_DIR}
  COMPONENT library
)

install(
  FILES ${BASEENCODE_HEADERS}
  DESTINATION include
)

configure_file("baseencode.pc.in" "baseencode.pc" @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/baseencode.pc" DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig/)
