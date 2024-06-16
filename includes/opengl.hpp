#pragma once
#include <math/vector.hpp>
namespace opengl {
inline float degrees_to_radians(float angle) { return 0.0174533 * angle; }
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
};
} // namespace opengl
