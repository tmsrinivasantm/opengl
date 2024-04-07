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
    opengl::vec3 travelled = opengl::vec3(
        cos(opengl::degrees_to_radians(yaw)) * cos(opengl::degrees_to_radians(pitch)),
        sin(opengl::degrees_to_radians(pitch)), 
        sin(opengl::degrees_to_radians(yaw)) * cos(opengl::degrees_to_radians(pitch)));
    travelled.normalize();

    camFront = travelled;

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
        opengl::vec3 cubePositions[] = {
            opengl::vec3( 0.0f,  0.0f,  0.0f), 
            opengl::vec3( 2.0f,  5.0f, -15.0f), 
            opengl::vec3(-1.5f, -2.2f, -2.5f),  
            opengl::vec3(-3.8f, -2.0f, -12.3f),  
            opengl::vec3( 2.4f, -0.4f, -3.5f),  
            opengl::vec3(-1.7f,  3.0f, -7.5f),  
            opengl::vec3( 1.3f, -2.0f, -2.5f),  
            opengl::vec3( 1.5f,  2.0f, -2.5f), 
            opengl::vec3( 1.5f,  0.2f, -1.5f), 
            opengl::vec3(-1.3f,  1.0f, -1.5f)  
        };

        projection = opengl::perspective(opengl::degrees_to_radians(fov), (800.0f/600.0f), 0.1f, 100.0f);
        opengl::translate(view, opengl::vec3(0.0f, 0.0f, -3.0f));

        // shaders
        opengl::shader myShader("../vert.shader", "../frag.shader");
        myShader.use();
        myShader.setMatrix4f("model", model);
        myShader.setMatrix4f("view", view);
        myShader.setMatrix4f("projection", projection);
        opengl::camera cam(camPosition, camFront);

        glEnable(GL_DEPTH_TEST);
        float currentFrame = 0.0f;
        float previousFrame = 0.0f;
        while (!glfwWindowShouldClose(window)) {

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPosCallback(window, mouseCallback);
            glfwSetScrollCallback(window, scrollCallback);

//          -------------------- Render -------------------
            myShader.use();
            vao.bind();
            texture.bind();

//          model matrix ops
            for(unsigned int i = 0; i < 10; i++) {
                model.initialize();
                opengl::translate(model, cubePositions[i]);
                float angle = 20.0f * i;
                opengl::rotate(model, opengl::degrees_to_radians(angle), (float[]){1.0f, 0.3f, 0.5f});
                myShader.setMatrix4f("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            // model.initialize();
            // opengl::rotate(model, (float)glfwGetTime(), (float[]){0.5f, 1.0f, 0.0f});
            // myShader.setMatrix4f("model", model);

//          view matrix ops
            currentFrame = (float)glfwGetTime();
            float deltaTime = currentFrame - previousFrame;
            previousFrame = currentFrame;
            float camSpeed = 3.5f;
            camSpeed  = camSpeed * deltaTime;
            keyboardInputResolve(window, camSpeed);

            cam.updateTarget(camPosition + camFront);
            cam.updatePosition(camPosition);
            view = cam.lookAt();
            myShader.setMatrix4f("view",view);

//          projection matrix ops
            projection = opengl::perspective(opengl::degrees_to_radians(fov), (800.0f/600.0f), 0.1f, 100.0f);
            myShader.setMatrix4f("projection", projection);

//          -----------------------------------------------

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}
