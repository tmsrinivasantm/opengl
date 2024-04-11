#include <glad/glad.h>
#include <GLFW/glfw3.h>

//local includes
#include <math/vector.hpp>
#include <opengl.hpp>
#include <objects/cube.hpp>
#include <primitives/array_buffers.hpp>
#include <objects/camera.hpp>
#include <math/matrices.hpp>
#include <primitives/shader.hpp>
#include <primitives/texture.hpp>

// global vars

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
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

        opengl::camera cam(window);

        float prevFrame = 0.0f;
        float currentFrame = 0.0f;
        glEnable(GL_DEPTH_TEST);
        while (!glfwWindowShouldClose(window)) {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            currentFrame = (float)glfwGetTime();
            float delta = currentFrame - prevFrame;
            prevFrame = currentFrame;

//          -------------------- Render -------------------
            projection = opengl::perspective(opengl::degrees_to_radians(45), 800.0f/600.0f, 0.1f, 100.0f);
            
            cam.init(delta);
            cam.focus();
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
