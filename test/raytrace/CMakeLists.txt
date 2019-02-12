set(shaders "plain_color.vert.glsl" "plain_color.frag.glsl")
foreach(shader ${shaders})
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/res/shader/${shader}" DESTINATION "${target_dir}/shader/")
endforeach()