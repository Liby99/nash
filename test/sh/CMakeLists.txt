set(shaders 
  # "${exec_dir}/shader/desk.vert.glsl" "${exec_dir}/shader/desk.frag.glsl"
  "${curr_dir}/res/shader/sh_sphere.vert.glsl" "${curr_dir}/res/shader/sh_sphere.frag.glsl"
)
foreach(shader ${shaders})
  file(COPY ${shader} DESTINATION "${target_dir}/shader/")
endforeach()

file(COPY "${curr_dir}/res/model/simp_desk.ply" DESTINATION "${target_dir}/model/")