set(shaders "sh_sphere.vert.glsl" "sh_sphere.frag.glsl")
foreach(shader ${shaders})
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/res/shader/${shader}" DESTINATION "${target_dir}/shader/")
endforeach()
