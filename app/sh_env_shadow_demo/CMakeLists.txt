copy_shader("sky_box")
copy_shader("sh_sphere")
copy_shader("coef_texture" FROM_CURRENT_RES)
copy_shader("sh_env_shadow" FROM_CURRENT_RES)

copy_cubemap("room" TO "room")
copy_cubemap("colors" TO "colors")

copy_image("head.bmp")

copy_model("dog.obj")
copy_model("teapot.obj")
copy_model("simp_desk.ply")

copy_coefs("obj/simp_desk.ply.coef")
copy_coefs("obj/dog.obj.dog.coef")
copy_coefs("obj/teapot.obj.defaultobject.coef")