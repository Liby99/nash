// clang-format off
#include "image/cube_map.h"
#include "image/texture.h"
#include "image/texture_2d.h"
#include "image/image.h"
#include "viewer/viewer.h"
#include "viewer/camera.h"
#include "viewer/context.h"
#include "viewer/canvas.h"
#include "viewer/scene.h"
#include "object/mesh.h"
#include "object/object.h"
#include "utility/script.h"
#include "utility/shader.h"
#include "utility/sampler.h"
#include "utility/path.h"
#include "utility/file.h"
#include "utility/transform.h"
#include "utility/math.h"
#include "utility/init.h"
#include "object/assimp/assimp_object.h"
#include "object/assimp/assimp_mesh.h"
#include "object/assimp/assimp_node.h"
#include "object/primitive/sphere.h"
#include "object/primitive/plane.h"
#include "object/primitive/cube.h"
#include "object/adhoc/point_cloud.h"
#include "object/adhoc/sky_box.h"
#include "object/adhoc/colored_point_cloud.h"
#include "adhoc/raytrace/intersection.h"
#include "adhoc/raytrace/box_tree_mesh.h"
#include "adhoc/raytrace/box_tree_node.h"
#include "adhoc/raytrace/ray.h"
#include "adhoc/raytrace/triangle.h"
#include "adhoc/raytrace/bounding_box.h"
#include "adhoc/script/rotator.h"
#include "adhoc/script/toggle.h"
#include "adhoc/script/third_person_camera.h"
#include "adhoc/script/first_person_camera.h"
#include "adhoc/sh/sh_coefs.h"
#include "adhoc/sh/sh.h"
#include "adhoc/sh/sky_box_sh_calculator.h"
#include "adhoc/sh/mesh_sh_calculator.h"
#include "adhoc/sh/sh_sphere.h"
#include "adhoc/sh/sh_color.h"
#include "adhoc/sh/sh_file.h"
