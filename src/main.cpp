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

    // operations
    float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                        0.0f,  0.0f,  0.5f, 0.0f};

    unsigned int vbo, shaderProgram;
    int vertexShader, fragmentShader;
    std::string vertShaderString, fragShaderString;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // compile shaders
    vertexShader = compileShader(GL_VERTEX_SHADER, "../vert.shader");
    vertexShader = compileShader(GL_FRAGMENT_SHADER, "../frag.shader");

    shaderProgram = glCreateProgram();

    // attach shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    // delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(shaderProgram);

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    glfwTerminate();
    return 0;
}
