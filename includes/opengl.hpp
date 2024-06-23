#pragma once
#include <math/vector.hpp>
namespace opengl {
inline float degrees_to_radians(float angle) { return 0.0174533 * angle; }
struct Material {
    int diffuse;
    int specular;
    float shininess;
};
enum Light_Type {
    DIRECTIONAL = 0,
    POINT = 1,
    SPOT = 2
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
