function(check_library name)
  if(NOT EXISTS "${curr_dir}/lib/${name}")
    message("Library ${name} not found.")
    message("Please make sure you use '--recursive' when you clone this repo.")
    message("If you forgot, you can still do \`git submodule update --init --recursive\`")
    message(FATAL_ERROR "Aborting due to not-found library ${name}")
  endif()
endfunction(check_library)