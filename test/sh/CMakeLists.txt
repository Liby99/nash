copy_shader("sh_sphere")
copy_shader("sky_box")
copy_shader("point_cloud")
copy_shader("colored_point_cloud")
copy_shader("env_shading" FROM_CURRENT_RES)

copy_model("simp_desk.ply")
copy_model("teapot.obj")

copy_cubemap("gracecathedral" TO "gracecathedral")
copy_cubemap("colors" TO "colors")
copy_cubemap("room" TO "room")