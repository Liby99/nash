copy_shader("plain_texture")
copy_shader("sky_box")
copy_shader("colored_point_cloud")

copy_image("head.bmp")
copy_image("cubemap/bridge3/posx.jpg" AS "bridge3_posx.jpg")
copy_image("cse169-proj2/gogo.png")

copy_cubemap("room" TO "room")
copy_cubemap("colors" TO "colors")