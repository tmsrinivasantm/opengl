#pragma once
#include <GLFW/glfw3.h>
#include <math/vector.hpp>
#include <math/matrices.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace opengl {
class camera {

public:
    camera(GLFWwindow* window);
    camera(GLFWwindow* window, const vec3 &camPosition);
    camera(GLFWwindow* window, const vec3 &camPosition, const vec3 &camTarget);
    void init(float deltaTime);
    matrix4f lookAt();
    glm::mat4 lookAt_glm();
    inline void setCamSpeed(float camSpeed) { this->camSpeed = camSpeed; }
    inline void focus() { isFocused = true; }
    inline void unfocus() { isFocused = false; }
    inline vec3 getPosition() { return position; }
    inline float getFOV() { return fov; }
    void reCalculate();
    // void mouseCallback(GLFWwindow *window, double xpos, double ypos);
private:
    GLFWwindow* window;
    bool isFocused = false;
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
