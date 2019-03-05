copy_shader("sky_box")
copy_shader("sh_env" FROM_CURRENT_RES)

copy_model("dog.obj")
copy_model("teapot.obj")
copy_model("simp_desk.ply")

copy_cubemap("gracecathedral" TO "gracecathedral")
copy_cubemap("colors" TO "colors")
copy_cubemap("room" TO "room")
copy_cubemap("bridge3" TO "bridge3")