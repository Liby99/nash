# Basic setups
cmake_minimum_required(VERSION 3.10)
project(nash)

# Options
option(NASH_BUILD_APP "Building application executables" ON)
option(NASH_BUILD_TEST "Building test executables" ON)
option(USE_OPEN_MP "Build use open mp" OFF)

# Global setup
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MACOSX_RPATH 1)
add_definitions(-DGL_SILENCE_DEPRECATION)

# MinGW Support
if(MINGW)
  set(NANOGUI_BUILD_SHARED OFF)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unknown-pragmas -Wno-unused-parameter -g \
    -Wno-int-in-bool-context -Wno-tautological-compare -Wno-maybe-uninitialized -Wno-return-type \
    -Wno-cast-function-type -Wno-implicit-fallthrough")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-pragmas -Wno-unused-parameter -frtti -g \
    -Wno-int-in-bool-context -Wno-tautological-compare -Wno-class-memaccess \
    -Wno-maybe-uninitialized -Wno-return-type -Wno-cast-function-type -Wno-implicit-fallthrough")
endif()

# Dependency checks
if (NOT IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/nanogui")
  message(FATAL_ERROR "The Nash dependency repositories (nanogui) is missing! "
    "You probably did not clone the project with --recursive. It is possible to recover "
    "by calling \"git submodule update --init --recursive\"")
endif()

# Include OpenMP
if(USE_OPEN_MP)
  find_package(OpenMP)
  if(OPENMP_FOUND)
    add_definitions(USE_OPEN_MP)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  endif()
endif()

# Include NanoGui
set(NANOGUI_BUILD_EXAMPLE OFF)
set(NANOGUI_BUILD_PYTHON OFF)
add_subdirectory(lib/nanogui EXCLUDE_FROM_ALL)
include_directories(lib/nanogui/include)
include_directories(${NANOGUI_EXTRA_INCS})
add_definitions(${NANOGUI_EXTRA_DEFS})

# Include Assimp
set(ASSIMP_NO_EXPORT ON)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_QT_VIEWER ON)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT FALSE)
set(ASSIMP_INCLUDE_FORMATS OBJ PLY OFF)
foreach(include_format ${ASSIMP_INCLUDE_FORMATS})
  set(ASSIMP_BUILD_${include_format}_IMPORTER TRUE)
endforeach()
add_subdirectory(lib/assimp EXCLUDE_FROM_ALL)
include_directories(lib/assimp/include)

# Include stb
# e.g. #include <stb_image.h>
include_directories(lib/stb/)

# Generate single header file using the script
execute_process(
  COMMAND python3 ${CMAKE_CURRENT_LIST_DIR}/script/generate_header.py nash
  ${CMAKE_CURRENT_LIST_DIR}/src/extern/
)

# Set Include Directory to Extern
include_directories(src/extern)

# Compile all the cpp files and link to `nash` library along with NanoGui
file(GLOB_RECURSE nash_sources src/intern/*.cpp src/extern/*.h)
set(nash ${nash_sources})
add_library(nash ${nash})
target_link_libraries(nash nanogui assimp ${NANOGUI_EXTRA_LIBS})

# Compile all the executable files
if(NASH_BUILD_TEST)
  file(GLOB_RECURSE tests test/*.cpp)
endif(NASH_BUILD_TEST)
if(NASH_BUILD_APP)
  file(GLOB_RECURSE apps app/*.cpp)
endif(NASH_BUILD_APP)
foreach(exec_source ${tests} ${apps})
  string(REPLACE ".cpp" "" target_path ${exec_source})
  string(REPLACE "${CMAKE_CURRENT_LIST_DIR}/" "" target_path ${target_path})
  get_filename_component(target_dir ${target_path} DIRECTORY)
  get_filename_component(target_name ${target_path} NAME)
  add_executable(${target_name} ${exec_source})
  set_target_properties(${target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${target_dir})
  target_link_libraries(${target_name} nash)
  include("${target_dir}/CMakeLists.txt" OPTIONAL)
endforeach()
