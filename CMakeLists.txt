cmake_minimum_required(VERSION 3.5)
project(howling C CXX)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(HOWLING_NAMESPACE "Custom namespace to use. Same as the game for ease of use." "howling")

set(BUILD_SHARED_LIBS OFF)

if (MSVC)
  add_compile_options("/MP")
endif()

file(GLOB THE_SOURCES CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hh)

find_package(magic_enum CONFIG REQUIRED)
find_package(boost_core REQUIRED CONFIG)
find_package(spdlog CONFIG REQUIRED)
find_package(sol2 CONFIG REQUIRED)
find_package(Lua REQUIRED)

set(RAYLIB_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(RAYLIB_BUILD_GAMES OFF CACHE BOOL "" FORCE)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/.wolfpack/raysan5/raylib")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/.wolfpack/metayeti/mINI")

add_library(${PROJECT_NAME} STATIC ${THE_SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC
  raylib
  magic_enum::magic_enum
  mINI
  spdlog::spdlog
  Boost::core
  sol2
  ${LUA_LIBRARIES}
)

set(HOWLING_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PUBLIC
  ${HOWLING_HEADERS}
  ${LUA_INCLUDE_DIR}
)

if (NOT HOWLING_NAMESPACE)
  set(HOWLING_NAMESPACE "howling")
endif()

message("Using namespace ${HOWLING_NAMESPACE}")

target_compile_definitions(${PROJECT_NAME} PRIVATE
  HOWLING_NAMESPACE=${HOWLING_NAMESPACE}
)

if (HOWLING_DOXYGEN)
  find_package(Doxygen)
  doxygen_add_docs(howling_doxygen ${CMAKE_CURRENT_SOURCE_DIR})
endif()
