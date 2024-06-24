#pragma once
#include <math/vector.hpp>
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
    vec3 Position;
    vec3 Normals;
    vec2 TexCoords;
};
struct Texture {
    unsigned int identifier;
    unsigned int type;
};
struct Material {
    int diffuse;
    int specular;
    float shininess;
};
struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
    vec3 direction;
    float outerCutoff;
    float innerCutoff;
    float constant;
    float linear;
    float quadratic;
    int type;
};
} // namespace opengl
