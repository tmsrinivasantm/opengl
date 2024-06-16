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
//glm
#include <glm/matrix.hpp>

// imgui includes

// global vars
opengl::vec3 lightPos(-2.0f, 0.0f, 0.0f);

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

        static constexpr float vertices[] = {
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
        };
        opengl::array_buffer vbo;
        opengl::vertex_array vao;
        vbo.bind();
        vao.bind();

        vbo.setData(vertices, sizeof(vertices));
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        opengl::shader baseShader("../shaders/base_material/vert.shader","../shaders/base_material/frag.shader");
        opengl::shader lightShader("../shaders/light_source/vert.shader","../shaders/light_source/frag.shader");
        baseShader.use();
        
        opengl::matrix4f projection;
        opengl::matrix4f view;
        glm::mat4 view_glm;
        opengl::matrix4f model;
        opengl::matrix4f newModel;

        opengl::camera cam(window);

        opengl::texture cat("../src/textures/cat_minimal.jpg");
        opengl::texture cat_spec("../src/textures/cat_minimal_specular.jpg");

        float prevFrame = 0.0f;
        float currentFrame = 0.0f;
        glEnable(GL_DEPTH_TEST);
        opengl::scale(newModel, opengl::vec3(0.25f, 0.25f, 0.25f));
        opengl::translate(newModel, lightPos);
        // opengl::Material gold = {
        //     // .ambient = opengl::vec3(0.75, 0.60648, 0.22648), // material's ambient and diffuse should be the same
        //     .ambient = opengl::vec3(0.75, 0.60648, 0.22648), // material's ambient and diffuse should be the same
        //     .diffuse = opengl::vec3(0.75, 0.60648, 0.22648),
        //     .specular = opengl::vec3(0.7, 0.556, 0.366),
        //     // .specular = opengl::vec3(0.7, 0.7, 0.7),
        //     .shininess = 32.0f
        // };
        opengl::Material cat_material = {
            .diffuse = 0,
            .specular = 1,
            .shininess = 32.0f
        };

        opengl::Light default_light = {
            .ambient = opengl::vec3(0.8, 0.8, 0.8),
            .diffuse = opengl::vec3(1.0, 1.0, 1.0),
            .specular = opengl::vec3(1.0, 1.0, 1.0),    // light's diffuse and specular should be the same
            .position = opengl::vec3(-2.0, 0.0, 0.0),
        };
        while (!glfwWindowShouldClose(window)) {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            currentFrame = (float)glfwGetTime();
            float delta = currentFrame - prevFrame;
            prevFrame = currentFrame;

//          -------------------- Render -------------------
            projection = opengl::perspective(opengl::degrees_to_radians(cam.getFOV()), 800.0f/600.0f, 0.1f, 100.0f);
            
            cam.init(delta);
            cam.focus();
            view_glm = cam.lookAt_glm();
            glActiveTexture(GL_TEXTURE0);
            cat.bind();
            glActiveTexture(GL_TEXTURE1);
            cat_spec.bind();

            baseShader.use();
            baseShader.setMatrix4f("model", model);
            baseShader.setMatrix4f("view", view_glm);
            baseShader.setMatrix4f("projection", projection);
            baseShader.setVec3("lookPos", cam.getPosition());
            baseShader.setMaterial("material", cat_material);
            baseShader.setLight("default_light", default_light);
            baseShader.setVec3("lightColour", opengl::vec3(1.0f, 1.0f, 1.0f));
            glDrawArrays(GL_TRIANGLES, 0, 36); 

            // light source
            float radius = 2.0f;
            opengl::vec3 translator((delta * sin(currentFrame) * radius), 0.0f, (delta * cos(currentFrame) * radius));
            default_light.position = default_light.position + translator;
            opengl::translate(newModel, translator);
            lightShader.use();
            lightShader.setMatrix4f("model", newModel);
            lightShader.setMatrix4f("view", view_glm);
            lightShader.setMatrix4f("projection", projection);
            glDrawArrays(GL_TRIANGLES, 0, 36); 

//          -----------------------------------------------

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}
