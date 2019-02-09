set(images "head.bmp" "cubemaps/bridge3/posx.jpg" "cse169-proj2/gogo.png")
foreach(image ${images})
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/res/image/${image}" DESTINATION "${target_dir}/image/")
endforeach()

set(shaders "plain_texture.vert.glsl" "plain_texture.frag.glsl")
foreach(shader ${shaders})
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/res/shader/${shader}" DESTINATION "${target_dir}/shader/")
endforeach()
