#include <objects/camera.hpp>
#include <opengl.hpp>

namespace opengl {
matlib::vec3 camPosition = matlib::vec3(0.0f, 0.0f, 3.0f);
matlib::vec3 camFront = matlib::vec3(0.0f, 0.0f, -1.0f);
matlib::vec3 WORLD_UP = matlib::vec3(0.0f, 1.0f, 0.0f);
unsigned int cam_cursor_capture_type = GLFW_CURSOR_DISABLED;
bool firstMouse = true;
float lastX = 300;
float lastY = 400;
float yaw = -90.0f;
float pitch;
float camFOV = 45.0f;
ImGuiIO outIO;

camera::camera(GLFWwindow *window)
    : position(matlib::vec3(0.0f, 0.0f, 3.0f)), window(window), target(matlib::vec3(0,0,0)) {
    reCalculate();
}
camera::camera(GLFWwindow *window, const matlib::vec3 &cameraPosition)
    : position(cameraPosition), window(window), target(matlib::vec3(0,0,0)) {
    camFront = matlib::vec3(0, 0, 0);
    camPosition = cameraPosition;
    reCalculate();
}
camera::camera(GLFWwindow *window, const matlib::vec3 &cameraPosition,
               const matlib::vec3 &cameraTarget)
    : position(cameraPosition), target(cameraTarget), window(window) {
    camPosition = cameraPosition;
    camFront = cameraTarget;
    reCalculate();
}
void camera::reCalculate() {
    fov = camFOV;
    position = camPosition;
    target = camFront;
    // vec3 direction = (position - (position + target)).normalize();
    right = target.cross(matlib::vec3(0.0f, 1.0f, 0.0f)).normalize();
    up = right.cross(target).normalize();
}
matlib::matrix4f camera::lookAt() {
    matlib::matrix4f result;

    glm::vec3 glm_position = glm::vec3(position[0], position[1], position[2]);
    glm::vec3 glm_target = glm::vec3(target[0], target[1], target[2]);
    result = glm::lookAt(glm_position, glm_position + glm_target, glm::vec3(0.0f, 1.0f, 0.0f));

    return result;
}

void camera::init(float deltaTime, ImGuiIO &io) {
    if (isFocused) {
        outIO = io;
        glfwSetInputMode(window, GLFW_CURSOR, cam_cursor_capture_type);
        glfwSetCursorPosCallback(window, mouseCallback);
        glfwSetScrollCallback(window, scrollCallback);
        keyboardInputResolve(window, deltaTime * camSpeed);
        reCalculate();
    }
}
void mouseCallback(GLFWwindow *window, double xpos, double ypos) {
    if (cam_cursor_capture_type == GLFW_CURSOR_NORMAL) {
        outIO.AddMousePosEvent(static_cast<float>(xpos), static_cast<float>(ypos));
        return;
    }

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    const float sensitivity = 0.1f;
    float XOffset = xpos - lastX; float YOffset = lastY - ypos;

    XOffset *= sensitivity;
    YOffset *= sensitivity;

    yaw += XOffset;
    pitch += YOffset;
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    camFront = matlib::vec3(cos(degrees_to_radians(yaw)) * cos(degrees_to_radians(pitch)),
                        sin(degrees_to_radians(pitch)),
                        sin(degrees_to_radians(yaw)) * cos(degrees_to_radians(pitch))).normalize();

    lastX = xpos;
    lastY = ypos;
}

void keyboardInputResolve(GLFWwindow *window, float camSpeed) {

    // if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    //     camPosition = camPosition - matlib::vec3(0.0f, 0.0f, camSpeed);
    // }
    // if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    //     camPosition = camPosition - matlib::vec3(camSpeed, 0.0f, 0.0f);
    // }
    // if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    //     camPosition = camPosition + matlib::vec3(0.0f, 0.0f, camSpeed);
    // }
    // if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    //     camPosition = camPosition + matlib::vec3(camSpeed, 0.0f, 0.0f);
    // }
    // if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
    //     camPosition = camPosition + matlib::vec3(0.0f, camSpeed, 0.0f);
    // }
    // if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
    //     camPosition = camPosition - matlib::vec3(0.0f, camSpeed, 0.0f);
    // }

    const float cameraSpeed = 0.05f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camPosition = camPosition + (camFront * camSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camPosition = camPosition - (camFront.cross(WORLD_UP).normalize() * camSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camPosition = camPosition - (camFront * camSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camPosition = camPosition + (camFront.cross(WORLD_UP).normalize() * camSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camPosition = camPosition + matlib::vec3(0.0f, camSpeed, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camPosition = camPosition - matlib::vec3(0.0f, camSpeed, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        cam_cursor_capture_type = GLFW_CURSOR_NORMAL;
        firstMouse = true;
    }
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
        cam_cursor_capture_type = GLFW_CURSOR_DISABLED;
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
