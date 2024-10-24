cmake_minimum_required(VERSION 3.5)
project(howling C CXX)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(HOWLING_NAMESPACE "Custom namespace to use. Same as the game for ease of use." "howling")
option(HOWLING_COUNT_ALLOCATIONS "Enable memory_profiler.hh functions" OFF)

set(BUILD_SHARED_LIBS OFF)

if (MSVC)
  add_compile_options("/MP")
  add_compile_options("/Zi")
  add_compile_options("/bigobj")
else()
  add_compile_options("-mbig-obj")
endif()

file(GLOB THE_SOURCES CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hh)
file(GLOB THE_LUA_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/assets/scripts/*.lua)

set(RAYLIB_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(RAYLIB_BUILD_GAMES OFF CACHE BOOL "" FORCE)
set(LUA_ENABLE_SHARED OFF CACHE BOOL "" FORCE)

function(add_vendor_library lib_name)
    set(VENDOR_DIR "${CMAKE_SOURCE_DIR}/../howling-vendor")
    set(BINARY_DIR "${CMAKE_BINARY_DIR}/${lib_name}")
    add_subdirectory("${VENDOR_DIR}/${lib_name}" "${BINARY_DIR}")
endfunction()

add_vendor_library("raylib-lua-sol")
add_vendor_library("magic_enum")
add_vendor_library("raylib")
add_vendor_library("mINI")
add_vendor_library("spdlog")
add_vendor_library("sol2")
add_vendor_library("Lua")

add_library(${PROJECT_NAME} STATIC ${THE_SOURCES} ${THE_LUA_SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC
  raylib
  magic_enum::magic_enum
  mINI
  spdlog::spdlog
  sol2
  lua_include
  raylib-lua-sol-hpp
)

set(HOWLING_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src" CACHE INTERNAL "")
set(HOWLING_ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets" CACHE INTERNAL "")

target_include_directories(${PROJECT_NAME} PUBLIC
  ${HOWLING_HEADERS}
  ${LUA_INCLUDE_DIR}
)

if (HOWLING_COUNT_ALLOCATIONS)
  target_compile_definitions(${PROJECT_NAME} PUBLIC
    LOG_ALLOCATIONS=ON
  )
endif()

if (NOT HOWLING_NAMESPACE)
  set(HOWLING_NAMESPACE "howling")
endif()

message("Using namespace ${HOWLING_NAMESPACE}")

target_compile_definitions(${PROJECT_NAME} PUBLIC
  HOWLING_NAMESPACE=${HOWLING_NAMESPACE}
)

if (HOWLING_DOXYGEN)
  find_package(Doxygen)
  doxygen_add_docs(howling_doxygen ${CMAKE_CURRENT_SOURCE_DIR})
endif()
