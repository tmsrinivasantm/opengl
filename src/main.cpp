#include "array_buffers.hpp"
#include "camera.hpp"
#include "matrices.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "vertex_array.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

//local includes
#include <vector.hpp>
#include <opengl.hpp>
#include <cube.hpp>

// global vars
opengl::vec3 camPosition = opengl::vec3(0.0f, 0.0f, 3.0f);
opengl::vec3 camFront = opengl::vec3(0.0f, 0.0f, -1.0f);
float lastX = 300;
float lastY = 400;
float yaw = -90.0f;
float pitch;
float fov = 45.0f;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    const float sensitivity = 0.1f;
    float XOffset = xpos - lastX;
    float YOffset = lastY - ypos;

    XOffset *= sensitivity;
    YOffset *= sensitivity;

    // std::cout << "x: " << XOffset << " y: " << YOffset << std::endl;
    yaw += XOffset;
    pitch += YOffset;
    if(pitch > 89.0f)
        pitch =  89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
    camFront = opengl::vec3(
        cos(opengl::degrees_to_radians(yaw)) * cos(opengl::degrees_to_radians(pitch)),
        sin(opengl::degrees_to_radians(pitch)), 
        sin(opengl::degrees_to_radians(yaw)) * cos(opengl::degrees_to_radians(pitch))).normalize();

    lastX = xpos;
    lastY = ypos;
}
void keyboardInputResolve(GLFWwindow *window,float camSpeed) {

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
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{

    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f; 
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Opengl", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//  operations
    {

        opengl::shader baseShader("../shaders/base_material/vert.shader","../shaders/base_material/frag.shader");
        
        opengl::matrix4f projection;
        opengl::matrix4f view;

        opengl::camera cam(camPosition);

        float prevFrame = 0.0f;
        float currentFrame = 0.0f;
        glEnable(GL_DEPTH_TEST);
        while (!glfwWindowShouldClose(window)) {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPosCallback(window, mouseCallback);
            glfwSetScrollCallback(window, scrollCallback);

            currentFrame = (float)glfwGetTime();
            float delta = currentFrame - prevFrame;
            prevFrame = currentFrame;

//          -------------------- Render -------------------
            baseShader.use();
            keyboardInputResolve(window, delta * 2.5f);

            projection = opengl::perspective(opengl::degrees_to_radians(fov), 800.0f/600.0f, 0.1f, 100.0f);
            
            cam.updatePosition(camPosition);
            view = cam.lookAt();
            baseShader.setMatrix4f("projection", projection);
            baseShader.setMatrix4f("view", view);

            opengl::cube cube(baseShader);

//          -----------------------------------------------

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}
