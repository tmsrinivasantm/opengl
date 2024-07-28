#pragma once
#include <GLFW/glfw3.h>
#include <math/vector.hpp>
#include <math/matrices.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

namespace opengl {
class camera {

public:
    camera(GLFWwindow* window);
    camera(GLFWwindow* window, const vec3 &camPosition);
    camera(GLFWwindow* window, const vec3 &camPosition, const vec3 &camTarget);
    void init(float deltaTime, ImGuiIO &io);
    matrix4f lookAt();
    glm::mat4 lookAt_glm();
    inline void setCamSpeed(float camSpeed) { this->camSpeed = camSpeed; }
    inline void focus() { isFocused = true; }
    inline void unfocus() { isFocused = false; }
    inline vec3 getPosition() { return position; }
    inline vec3 getTarget() { return target; }
    inline float getFOV() { return fov; }
    void reCalculate();
    // void mouseCallback(GLFWwindow *window, double xpos, double ypos);
    bool isFocused = false;
private:
    GLFWwindow* window;
    vec3 position;
    vec3 target;
    vec3 up;
    vec3 right;
    float camSpeed = 2.5f;
    float fov = 45.0;
};
void keyboardInputResolve(GLFWwindow *window,float camSpeed);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
}
