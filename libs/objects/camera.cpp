#include <camera.hpp>

namespace opengl {
opengl::vec3 camPosition = opengl::vec3(0.0f, 0.0f, 3.0f);
opengl::vec3 camFront = opengl::vec3(0.0f, 0.0f, -1.0f);
float lastX = 300;
float lastY = 400;
float yaw = -90.0f;
float pitch;
float fov = 45.0f;

camera::camera(GLFWwindow *window)
    : position(vec3(0.0f, 0.0f, 3.0f)), window(window) {
    target = vec3(0, 0, 0);
    vec3 direction = (position - target).normalize();
    vec3 worldUp = vec3(0.0f, 1.0f, 0.0f);
    right = worldUp.cross(direction).normalize();
    up = direction.cross(right);
}
camera::camera(GLFWwindow *window, const vec3 &cameraPosition)
    : position(cameraPosition), window(window) {
    target = vec3(0, 0, 0);
    vec3 direction = (position - target).normalize();
    vec3 worldUp = vec3(0.0f, 1.0f, 0.0f);
    right = worldUp.cross(direction).normalize();
    up = direction.cross(right);
}
camera::camera(GLFWwindow *window, const vec3 &cameraPosition,
               const vec3 &cameraTarget)
    : position(cameraPosition), target(cameraTarget), window(window) {
    vec3 direction = (position - target).normalize();
    vec3 worldUp = vec3(0.0f, 1.0f, 0.0f);
    right = worldUp.cross(direction).normalize();
    up = direction.cross(right);
}
void camera::updatePosition(const vec3 &camPosition) {
    position = camPosition;
    vec3 direction = (position - target).normalize();
    right = vec3(0.0f, 1.0f, 0.0f).cross(direction).normalize();
    up = direction.cross(right);
}
void camera::updateTarget(const vec3 &camTarget) {
    target = camTarget;
    vec3 direction = (position - target).normalize();
    right = vec3(0.0f, 1.0f, 0.0f).cross(direction).normalize();
    up = direction.cross(right);
}
matrix4f camera::lookAt() {
    matrix4f result;

    vec3 direction = (position - target).normalize();
    result.make_matrix4f(right.normalize(), up.normalize(), direction);
    translate(result, position * -1.0f);

    return result;
}
void camera::init(float deltaTime) {
    if (isFocused) {
        glfwSetCursorPosCallback(window, mouseCallback);
        glfwSetScrollCallback(window, scrollCallback);
        keyboardInputResolve(window, deltaTime * camSpeed);
        updatePosition(camPosition);
        updateTarget(camPosition + camFront);
    }
}
void mouseCallback(GLFWwindow *window, double xpos, double ypos) {
    const float sensitivity = 0.1f;
    float XOffset = xpos - lastX;
    float YOffset = lastY - ypos;

    XOffset *= sensitivity;
    YOffset *= sensitivity;

    // std::cout << "x: " << XOffset << " y: " << YOffset << std::endl;
    yaw += XOffset;
    pitch += YOffset;
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    camFront = opengl::vec3(cos(opengl::degrees_to_radians(yaw)) *
                                cos(opengl::degrees_to_radians(pitch)),
                            sin(opengl::degrees_to_radians(pitch)),
                            sin(opengl::degrees_to_radians(yaw)) *
                                cos(opengl::degrees_to_radians(pitch)))
                   .normalize();

    lastX = xpos;
    lastY = ypos;
}

void keyboardInputResolve(GLFWwindow *window, float camSpeed) {

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camPosition = camPosition - opengl::vec3(0.0f, 0.0f, camSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camPosition = camPosition - opengl::vec3(camSpeed, 0.0f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camPosition = camPosition + opengl::vec3(0.0f, 0.0f, camSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camPosition = camPosition + opengl::vec3(camSpeed, 0.0f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camPosition = camPosition + opengl::vec3(0.0f, camSpeed, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camPosition = camPosition - opengl::vec3(0.0f, camSpeed, 0.0f);
    }
}

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {

    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}
} // namespace opengl
