#pragma once
#include <GLFW/glfw3.h>
#include "../vendor/matlib/includes/vec.hpp"
#include "../vendor/matlib/includes/matrices.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

namespace opengl {
class camera {

public:
    camera(GLFWwindow* window);
    camera(GLFWwindow* window, const matlib::vec3 &camPosition);
    camera(GLFWwindow* window, const matlib::vec3 &camPosition, const matlib::vec3 &camTarget);
    void init(float deltaTime, ImGuiIO &io);
    matlib::matrix4f lookAt();
    inline void setCamSpeed(float camSpeed) { this->camSpeed = camSpeed; }
    inline void focus() { isFocused = true; }
    inline void unfocus() { isFocused = false; }
    inline matlib::vec3 getPosition() { return position; }
    inline matlib::vec3 getTarget() { return target; }
    inline float getFOV() { return fov; }
    void reCalculate();
    // void mouseCallback(GLFWwindow *window, double xpos, double ypos);
    bool isFocused = false;
private:
    GLFWwindow* window;
    matlib::vec3 position;
    matlib::vec3 target;
    matlib::vec3 up = matlib::vec3(0.0f, 0.1f, 0.0f);
    matlib::vec3 right;
    float camSpeed = 2.5f;
    float fov = 45.0;
};
void keyboardInputResolve(GLFWwindow *window,float camSpeed);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
}
