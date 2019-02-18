copy_image("head.bmp")
copy_image("cubemaps/bridge3/posx.jpg")
copy_image("cse169-proj2/gogo.png")

copy_image("cubemaps/room/posx.jpg" DESTINATION "room")
copy_image("cubemaps/room/negx.jpg" DESTINATION "room")
copy_image("cubemaps/room/posy.jpg" DESTINATION "room")
copy_image("cubemaps/room/negy.jpg" DESTINATION "room")
copy_image("cubemaps/room/posz.jpg" DESTINATION "room")
copy_image("cubemaps/room/negz.jpg" DESTINATION "room")

copy_shader("plain_texture")
copy_shader("env_map")