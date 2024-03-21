#include <glad/glad.h>
#include <GLFW/glfw3.h>

//local includes
#include <element_buffer.hpp>
#include <array_buffers.hpp>
#include <vertex_array.hpp>
#include <texture.hpp>
#include <shader.hpp>
#include <matrices.hpp>
#include <vector.hpp>
#include <camera.hpp>

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

    {

//         float vertices[] = {
// //               position           colour       textures
//              0.5f,  0.5f, 0.0f,  1.0, 0.0, 0.0, 1.0f, 1.0f,
//              0.5f, -0.5f, 0.0f,  0.0, 1.0, 0.0, 1.0f, 0.0f,
//             -0.5f, -0.5f, 0.0f,  0.0, 0.0, 1.0, 0.0f, 0.0f,
//             -0.5f,  0.5f, 0.0f,  1.0, 1.0, 1.0, 0.0f, 1.0f,
//              0.5f,  0.5f,-1.0f,  1.0, 0.0, 0.0, 1.0f, 1.0f,
//              0.5f, -0.5f,-1.0f,  0.0, 1.0, 0.0, 1.0f, 0.0f,
//             -0.5f, -0.5f,-1.0f,  0.0, 0.0, 1.0, 0.0f, 0.0f,
//             -0.5f,  0.5f,-1.0f,  1.0, 1.0, 1.0, 0.0f, -1.0f
//         };

           float vertices[] = {
           -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
           0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
           0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
           0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
           -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
           -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

           -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
           0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
           0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
           0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
           -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
           -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

           -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
           -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
           -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
           -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
           -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
           -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

           0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
           0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
           0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
           0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
           0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
           0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

           -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
           0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
           0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
           0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
           -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
           -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

           -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
           0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
           0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
           0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
           -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
           -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };
        unsigned int indices[] = {
            0,1,3,1,2,3,
            4,5,0,5,1,0,
            4,5,7,5,6,7,
            3,2,7,3,6,8,
            4,0,7,0,3,7,
            5,1,6,1,2,6
        };

        opengl::vertex_array vao;

        opengl::array_buffer vbo;
        vbo.setData(vertices, sizeof(vertices));

        // opengl::element_buffer ebo;
        // ebo.setData(indices, sizeof(indices));

        //position attribute set
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // colour attribute set
        // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
        // glEnableVertexAttribArray(1);
        // texture attribute set
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(2);

        // textures
        opengl::texture texture("../src/textures/cat_minimal.jpg");

        // vert operations
        opengl::matrix4f model;
        opengl::matrix4f view;
        opengl::matrix4f projection;

        projection = opengl::perspective(opengl::degrees_to_radians(45.0f), (800.0f/600.0f), 0.1f, 100.0f);
        opengl::translate(view, opengl::vec3(0.0f, 0.0f, -3.0f));

        // shaders
        opengl::shader myShader("../vert.shader", "../frag.shader");
        myShader.use();
        myShader.setMatrix4f("model", model);
        myShader.setMatrix4f("view", view);
        myShader.setMatrix4f("projection", projection);
        opengl::camera cam(opengl::vec3(0.0f, 0.0f, 3.0f));

        glEnable(GL_DEPTH_TEST);
        while (!glfwWindowShouldClose(window)) {

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//          -------------------- Render -------------------
            myShader.use();
            vao.bind();
            texture.bind();
            model.initialize();
            opengl::rotate(model, (float)glfwGetTime(), (float[]){0.5f, 1.0f, 0.0f});
            myShader.setMatrix4f("model", model);

            const float radius = 3.0f;
            float camX = sin(glfwGetTime()) * radius;
            float camZ = cos(glfwGetTime()) + radius;
            // float camX = ;
            // float camZ = -3.0f;
            cam.updatePosition(opengl::vec3(camX, 0.0f, camZ));
            view = cam.lookAt();
            myShader.setMatrix4f("view",view);

            glDrawArrays(GL_TRIANGLES, 0, 36);
            // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

//          -----------------------------------------------

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

    }

    glfwTerminate();
    return 0;
}
