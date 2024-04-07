#include <camera.hpp>

namespace opengl {
camera::camera() : position(vec3(0.0f, 0.0f, 3.0f)) {
    target = vec3(0, 0, 0);
    vec3 direction = position - target;
    direction.normalize();
    vec3 worldUp = vec3(0.0f, 1.0f, 0.0f);
    right = worldUp.cross(direction);
    right.normalize();
    up = direction.cross(right);
}
camera::camera(const vec3 &camPosition) : position(camPosition) {
    target = vec3(0, 0, 0);
    vec3 direction = position - target;
    direction.normalize();
    vec3 worldUp = vec3(0.0f, 1.0f, 0.0f);
    right = worldUp.cross(direction);
    right.normalize();
    up = direction.cross(right);
}
camera::camera(const vec3 &camPosition, const vec3 &camTarget)
    : position(camPosition), target(camTarget) {
    vec3 direction = position - target;
    direction.normalize();
    vec3 worldUp = vec3(0.0f, 1.0f, 0.0f);
    right = worldUp.cross(direction);
    right.normalize();
    up = direction.cross(right);
}
void camera::updatePosition(const vec3 &camPosition) {
    position = camPosition;
    vec3 direction = position - target;
    direction.normalize();
    right = vec3(0.0f, 1.0f, 0.0f).cross(direction);
    up = direction.cross(right);
}
void camera::updateTarget(const vec3 &camTarget) {
    target = camTarget;
    vec3 direction = position - target;
    direction.normalize();
    right = vec3(0.0f, 1.0f, 0.0f).cross(direction);
    up = direction.cross(right);
}
matrix4f camera::lookAt() {
    matrix4f result;

    vec3 direction = position - target;
    direction.normalize();
    right.normalize();
    up.normalize();
    result.make_matrix4f(right, up, direction);
    translate(result, position * -1.0f);

    return result;
}
} // namespace opengl
