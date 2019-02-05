# Basic setups
cmake_minimum_required(VERSION 3.5)
project(nash)

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

# Generate single header file using the script
execute_process(
  COMMAND python3 ${CMAKE_CURRENT_LIST_DIR}/script/generate_header.py nash
  ${CMAKE_CURRENT_LIST_DIR}/src/extern/
)

# Set Include Directory to Extern
include_directories(src/extern)

# Compile all the cpp files and link to `nash` library along with NanoGui
file(
  GLOB nash_sources
  src/intern/**/*.cpp src/extern/**/*.h
)
set(nash ${nash_sources})
add_library(nash ${nash})
target_link_libraries(nash nanogui ${NANOGUI_EXTRA_LIBS})

# Compile all the executable files
file(GLOB exec_sources app/*.cpp app/**/*.cpp test/*.cpp test/**/*.cpp)
foreach(exec_source ${exec_sources})
  string(REPLACE ".cpp" "" temp_path ${exec_source})
  string(REPLACE "${CMAKE_CURRENT_LIST_DIR}/" "" temp_path ${temp_path})
  get_filename_component(temp_dir ${temp_path} DIRECTORY)
  get_filename_component(temp_name ${temp_path} NAME)
  add_executable(${temp_name} ${exec_source})
  set_target_properties(${temp_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${temp_dir})
  target_link_libraries(${temp_name} nash)
  include("${temp_dir}/CMakeLists.txt" OPTIONAL)
endforeach(exec_source ${exec_sources})
