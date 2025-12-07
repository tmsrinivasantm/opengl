#pragma once
#include "../vendor/matlib/includes/vec.hpp"
namespace opengl {
inline float degrees_to_radians(float angle) { return 0.0174533 * angle; }
enum Light_Type {
    DIRECTIONAL = 0,
    POINT = 1,
    SPOT = 2
};
enum Texture_Type {
    DIFFUSE = 0,
    SPECULAR = 1
};
struct vertex {
    matlib::vec3 Position;
    matlib::vec3 Normals;
    matlib::vec2 TexCoords;
};
struct Material {
    int diffuse;
    int specular;
    float shininess;
};
struct Light {
    matlib::vec3 ambient;
    matlib::vec3 diffuse;
    matlib::vec3 specular;
    matlib::vec3 position;
    matlib::vec3 direction;
    float outerCutoff;
    float innerCutoff;
    float constant;
    float linear;
    float quadratic;
    int type;
};
} // namespace opengl
