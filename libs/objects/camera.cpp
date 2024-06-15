#include <objects/camera.hpp>
#include <opengl.hpp>

namespace opengl {
opengl::vec3 camPosition = opengl::vec3(0.0f, 0.0f, 3.0f);
opengl::vec3 camFront = opengl::vec3(0.0f, 0.0f, -1.0f);
bool firstMouse = true;
float lastX = 300;
float lastY = 400;
float yaw = -90.0f;
float pitch;
float camFOV = 45.0f;

camera::camera(GLFWwindow *window)
    : position(vec3(0.0f, 0.0f, 3.0f)), window(window), target(vec3(0,0,0)) {
    reCalculate();
}
camera::camera(GLFWwindow *window, const vec3 &cameraPosition)
    : position(cameraPosition), window(window), target(vec3(0,0,0)) {
    camFront = vec3(0, 0, 0);
    reCalculate();
}
camera::camera(GLFWwindow *window, const vec3 &cameraPosition,
               const vec3 &cameraTarget)
    : position(cameraPosition), target(cameraTarget), window(window) {
    reCalculate();
}
void camera::reCalculate() {
    fov = camFOV;
    position = camPosition;
    target = camFront;
    // vec3 direction = (position - (position + target)).normalize();
    right = target.cross(opengl::vec3(0.0f, 1.0f, 0.0f)).normalize();
    up = right.cross(target).normalize();
}
glm::mat4 camera::lookAt_glm() {
    glm::vec3 glm_position = glm::vec3(position[0], position[1], position[2]);
    glm::vec3 glm_target = glm::vec3(target[0], target[1], target[2]);
    return glm::lookAt(glm_position, glm_position + glm_target, glm::vec3(0.0f, 1.0f, 0.0f));
}
matrix4f camera::lookAt() {
    matrix4f result;

    // vec3 direction = (position - (position + target));
    result.make_matrix4f(right.normalize(), up.normalize(), target.normalize());
    translate(result, position * -1.0f);

    return result;
}

void camera::init(float deltaTime) {
    if (isFocused) {
        glfwSetCursorPosCallback(window, mouseCallback);
        glfwSetScrollCallback(window, scrollCallback);
        keyboardInputResolve(window, deltaTime * camSpeed);
        reCalculate();
    }
}
void mouseCallback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    const float sensitivity = 0.1f;
    float XOffset = xpos - lastX;
    float YOffset = lastY - ypos;

    XOffset *= sensitivity;
    YOffset *= sensitivity;

    yaw += XOffset;
    pitch += YOffset;
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    camFront = opengl::vec3(cos(degrees_to_radians(yaw)) * cos(degrees_to_radians(pitch)),
                        sin(degrees_to_radians(pitch)),
                        sin(degrees_to_radians(yaw)) * cos(degrees_to_radians(pitch))).normalize();

    lastX = xpos;
    lastY = ypos;
}

void keyboardInputResolve(GLFWwindow *window, float camSpeed) {

    // if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    //     camPosition = camPosition - opengl::vec3(0.0f, 0.0f, camSpeed);
    // }
    // if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    //     camPosition = camPosition - opengl::vec3(camSpeed, 0.0f, 0.0f);
    // }
    // if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    //     camPosition = camPosition + opengl::vec3(0.0f, 0.0f, camSpeed);
    // }
    // if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    //     camPosition = camPosition + opengl::vec3(camSpeed, 0.0f, 0.0f);
    // }
    // if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
    //     camPosition = camPosition + opengl::vec3(0.0f, camSpeed, 0.0f);
    // }
    // if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
    //     camPosition = camPosition - opengl::vec3(0.0f, camSpeed, 0.0f);
    // }

    const float cameraSpeed = 0.05f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camPosition = camPosition + (camFront * camSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camPosition = camPosition - (camFront.cross(vec3(0.0f, 1.0f, 0.0f)).normalize() * camSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camPosition = camPosition - (camFront * camSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camPosition = camPosition + (camFront.cross(vec3(0.0f, 1.0f, 0.0f)).normalize() * camSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camPosition = camPosition + opengl::vec3(0.0f, camSpeed, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camPosition = camPosition - opengl::vec3(0.0f, camSpeed, 0.0f);
    }

}

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {

    camFOV -= (float)yoffset;
    if (camFOV < 1.0f)
        camFOV = 1.0f;
    if (camFOV > 45.0f)
        camFOV = 45.0f;
}
} // namespace opengl
