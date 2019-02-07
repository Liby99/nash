# Basic setups
cmake_minimum_required(VERSION 3.5)
project(nash)

# Options
option(NASH_BUILD_APP "Building application executables" ON)
option(NASH_BUILD_TEST "Building test executables" ON)

# Global setup
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MACOSX_RPATH 1)
add_definitions(-DGL_SILENCE_DEPRECATION)

# Dependency checks
if (NOT IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/nanogui")
  message(FATAL_ERROR "The Nash dependency repositories (nanogui) is missing! "
    "You probably did not clone the project with --recursive. It is possible to recover "
    "by calling \"git submodule update --init --recursive\"")
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
  string(REPLACE ".cpp" "" temp_path ${exec_source})
  string(REPLACE "${CMAKE_CURRENT_LIST_DIR}/" "" temp_path ${temp_path})
  get_filename_component(temp_dir ${temp_path} DIRECTORY)
  get_filename_component(temp_name ${temp_path} NAME)
  add_executable(${temp_name} ${exec_source})
  set_target_properties(${temp_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${temp_dir})
  target_link_libraries(${temp_name} nash)
  include("${temp_dir}/CMakeLists.txt" OPTIONAL)
endforeach()
