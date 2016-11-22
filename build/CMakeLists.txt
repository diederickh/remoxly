cmake_minimum_required(VERSION 2.8)
project(Remoxly)
set(bd ${CMAKE_CURRENT_LIST_DIR}/../)
set(id ${bd}/include)
set(sd ${bd}/src)
include_directories(${id})

# Determine the name of the remoxly library.
# ------------------------------------------
set(build_flag "release")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(build_flag "debug")
  if (APPLE)
    set (CMAKE_CXX_FLAGS "-fsanitize=address ${CMAKE_CXX_FLAGS} -g")
  endif()
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -ffast-math -std=c++11 -g -funroll-loops -fslp-vectorize-aggressive")
endif()

set(compiler_name "unknown")
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(compiler_name "clang")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  if ("${MSVC_VERSION}" STREQUAL "1900")
    set(compiler_name "msvc2015")
  elseif ("${MSVC_VERSION}" STREQUAL "1800")
    set(compiler_name "msvc2013")
  elseif ("${MSVC_VERSION}" STREQUAL "1700")
    set(compiler_name "msvc2012")
  elseif ("${MSVC_VERSION}" STREQUAL "1600")
    set(compiler_name "msvc2010")
  endif()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(compiler_name "gnu")
endif()

set(arch "32")
if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
  set(arch "64")
endif()

set(suffix "a")
if (WIN32)
  set(suffix "lib")
endif()

set(remoxly_lib_name "remoxly-${build_flag}-${compiler_name}-${arch}.${suffix}")

if (WIN32)
  list(APPEND remoxly_libs
    ws2_32.lib
    ${bd}/lib/${remoxly_lib_name}
    )
elseif(APPLE)
    list(APPEND remoxly_libs
      ${bd}/lib/lib${remoxly_lib_name}
    )
endif()

# Create example executable
# ------------------------------------------
add_executable(remoxly_example ${sd}/example.cpp)
target_link_libraries(remoxly_example ${remoxly_libs})
install(TARGETS remoxly_example DESTINATION bin)
