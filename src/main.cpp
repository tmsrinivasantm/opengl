#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

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
        std::cout << "FAILED TO COMPILE SHADER => " << infolog << std::endl;
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
    float vertices[] = {-0.5f, -0.5f, 0.0f,
                         0.5f, -0.5f, 0.0f,
                         0.0f,  0.5f, 0.0f};

    unsigned int vbo, vao;

    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindVertexArray(vao);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

//      -------------------- Render -------------------

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

//      -----------------------------------------------

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
