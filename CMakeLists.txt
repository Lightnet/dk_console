cmake_minimum_required(VERSION 3.14)
project(raylib_dk_console LANGUAGES C CXX)

# Set up cache directory for built artifacts
set(CACHE_DIR "${CMAKE_BINARY_DIR}/cache")
file(MAKE_DIRECTORY ${CACHE_DIR})

if(NOT EXISTS "${CMAKE_BINARY_DIR}/cmake/CPM.cmake")
    file(DOWNLOAD
        "https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/CPM.cmake"
        "${CMAKE_BINARY_DIR}/cmake/CPM.cmake"
    )
endif()
include(${CMAKE_BINARY_DIR}/cmake/CPM.cmake)

# raylib
CPMAddPackage(
    NAME raylib
    GITHUB_REPOSITORY raysan5/raylib
    GIT_TAG 5.5
    OPTIONS
        "BUILD_EXAMPLES OFF"
        "BUILD_GAMES OFF"
        "BUILD_SHARED_LIBS ON"
)

# Check and configure raylib.dll
set(RAYLIB_DLL_SRC "${raylib_BINARY_DIR}/raylib/Debug/raylib.dll")
set(RAYLIB_DLL "${CACHE_DIR}/raylib.dll")
if(NOT EXISTS ${RAYLIB_DLL} OR "${raylib_SOURCE_DIR}/src/raylib.h" IS_NEWER_THAN ${RAYLIB_DLL})
    add_custom_command(
        OUTPUT ${RAYLIB_DLL}
        COMMAND ${CMAKE_COMMAND} -E echo "Copying raylib.dll from ${RAYLIB_DLL_SRC} to ${RAYLIB_DLL}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${RAYLIB_DLL_SRC} ${RAYLIB_DLL}
        DEPENDS raylib
        COMMENT "Caching raylib.dll from ${RAYLIB_DLL_SRC}"
    )
    add_custom_target(raylib_cache DEPENDS ${RAYLIB_DLL})
endif()

set(app_lua raylib_dk_console)
# MAIN
add_executable(${app_lua} 
  src/main.c
  # src/test.c
  src/dk_console.c
  src/dk_ui.c
)

target_compile_definitions(${app_lua} PUBLIC
  -D_CRT_SECURE_NO_WARNINGS
)

if(TARGET raylib_cache)
    add_dependencies(${app_lua} raylib_cache)
endif()

target_include_directories(${app_lua} PRIVATE
    ${raylib_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${app_lua} PRIVATE
  raylib
)

if(WIN32)
  target_link_libraries(${app_lua} PRIVATE ws2_32 winmm)
endif()

# Copy DLLs to output directory
set(RAYLIB_DLL_DEST "${CMAKE_BINARY_DIR}/Debug/raylib.dll")
if(NOT EXISTS ${RAYLIB_DLL_DEST})
  add_custom_command(TARGET ${app_lua} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
          "${RAYLIB_DLL}"
          "$<TARGET_FILE_DIR:${app_lua}>/raylib.dll"
      COMMENT "Copying raylib.dll to output directory"
  )
endif()

# Copy entire assets folder (including subdirectories) to build output
set(ASSETS_SRC_DIR "${CMAKE_SOURCE_DIR}/Resources")  # Use quotes and forward slashes
# set(ASSETS_DEST_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/resources")
set(ASSETS_DEST_DIR "${CMAKE_BINARY_DIR}/$<CONFIG>/Resources")

# Check if assets directory exists
if(NOT EXISTS "${ASSETS_SRC_DIR}")
    message(WARNING "Assets directory '${ASSETS_SRC_DIR}' does not exist. Creating empty directory in build output.")
    # file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>/Resources)
endif()

# Add custom command to copy entire assets directory
add_custom_command(TARGET ${app_lua} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${ASSETS_DEST_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${ASSETS_SRC_DIR}" "${ASSETS_DEST_DIR}"
    COMMENT "Copying assets directory to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/Resources"
)