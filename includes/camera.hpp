#pragma once
#include <vector.hpp>
#include <matrices.hpp>

namespace opengl {
class camera {

public:
    camera();
    camera(const vec3 &camPosition);
    camera(const vec3 &camPosition, const vec3 &camTarget);
    void updatePosition(const vec3 &camPosition);
    void updateTarget(const vec3 &camTarget);
    matrix4f lookAt();
private:
    vec3 position;
    vec3 target;
    vec3 up;
    vec3 right;
};
}
