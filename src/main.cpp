#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

//local includes
#include <element_buffer.hpp>
#include <array_buffers.hpp>
#include <vertex_array.hpp>
#include <texture.hpp>
#include <shader.hpp>

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

    // operations
    {
        float vertices[] = {
//               position           colour       textures
             0.5f,  0.5f, 0.0f,  1.0, 0.0, 0.0, 1.0f, 1.0f,
             0.5f, -0.5f, 0.0f,  0.0, 1.0, 0.0, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,  0.0, 0.0, 1.0, 0.0f, 0.0f,
            -0.5f,  0.5f, 0.0f,  1.0, 1.0, 1.0, 0.0f, 1.0f
        };
        unsigned int indices[] = {0,1,3,1,2,3};
        float texture_coords[] = {
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f
        };

        opengl::vertex_array vao;

        opengl::array_buffer vbo;
        vbo.setData(vertices, sizeof(vertices));

        opengl::element_buffer ebo;
        ebo.setData(indices, sizeof(indices));

        //position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // colour
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);
        // texture
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
        glEnableVertexAttribArray(2);

        // shaders
        opengl::shader myShader("../vert.shader", "../frag.shader");


        // textures
        opengl::texture texture("../src/textures/abstract_blured.jpg");
        opengl::texture texture2("../src/textures/david.jpg");

        while (!glfwWindowShouldClose(window)) {

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

//          -------------------- Render -------------------

            myShader.use();
            vao.bind();
            texture2.bind();

            glm::mat4 transform = glm::mat4(1.0f);
            transform = glm::rotate(transform, (float)glfwGetTime(),glm::vec3(0.0f,0.0f,1.0f));
            myShader.setMatrix4f("transform", transform);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            texture.bind();
            transform = glm::mat4(1.0f);
            transform = glm::rotate(transform, -(float)glfwGetTime(),glm::vec3(0.0f,0.0f,1.0f));
            myShader.setMatrix4f("transform", transform);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

//          -----------------------------------------------

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

    }

    glfwTerminate();
    return 0;
}
