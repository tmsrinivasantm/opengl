#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

//local includes
#include <element_buffer.hpp>
#include <array_buffers.hpp>
#include <vertex_array.hpp>
#include <texture.hpp>

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
std::string readFile(const std::string &filename) {
    std::ifstream file(filename);
    std::string line;
    std::stringstream ss;

    while(getline(file, line)){
        ss << line << '\n';
    }
    return ss.str();
}

int compileShader(unsigned int shaderType, const std::string &filename) {
    const char* shaderSource; 
    std::string shaderString;
    char infolog[512];
    int shader, success;
    shaderString = readFile(filename);
    shaderSource = shaderString.c_str();
    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource,NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(shader, 512, NULL, infolog);
        if (shaderType == GL_VERTEX_SHADER)
            std::cout << "FAILED TO COMPILE VERTEX SHADER => " << infolog << std::endl;
        else if (shaderType == GL_FRAGMENT_SHADER)
            std::cout << "FAILED TO COMPILE FRAGMENT SHADER => " << infolog << std::endl;
    }

    return shader;
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

    int vertexShader, fragmentShader;
    unsigned int shaderProgram;
    std::string vertShaderString, fragShaderString;
    // compile shaders
    vertexShader = compileShader(GL_VERTEX_SHADER, "../vert.shader");
    fragmentShader = compileShader(GL_FRAGMENT_SHADER, "../frag.shader");

    shaderProgram = glCreateProgram();

    // attach shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    // delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

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


        // textures
        opengl::texture texture("../src/textures/abstract_blured.jpg");

        while (!glfwWindowShouldClose(window)) {

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

//          -------------------- Render -------------------

            glUseProgram(shaderProgram);
            vao.bind();
            texture.bind();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

//          -----------------------------------------------

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glDeleteProgram(shaderProgram);
    }

    glfwTerminate();
    return 0;
}
