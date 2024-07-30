#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

//local includes
#include <math/vector.hpp>
#include <opengl.hpp>
#include <objects/cube.hpp>
#include <primitives/array_buffers.hpp>
#include <objects/camera.hpp>
#include <math/matrices.hpp>
#include <primitives/shader.hpp>
#include <primitives/texture.hpp>
#include <model/model.hpp>
//glm
#include <glm/matrix.hpp>

// imgui includes
#include <deps/imgui.h>
#include <deps/imgui_impl_glfw.h>
#include <deps/imgui_impl_opengl3.h>

// global vars

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

std::vector<opengl::Light> lightSources;

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
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");


    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//  operations
    {

        opengl::Model backpack("../src/models/backpack/backpack.obj");
        opengl::shader baseShader("../shaders/base_material/vert.shader","../shaders/base_material/frag.shader");
        opengl::shader lightSourceShader("../shaders/light_source/vert.shader","../shaders/light_source/frag.shader");
        opengl::shader directionlLightShader("../shaders/directional_light/vert.shader", "../shaders/directional_light/frag.shader");
        opengl::shader pointLightShader("../shaders/point_light/vert.shader", "../shaders/point_light/frag.shader");
        opengl::shader spotlLightShader("../shaders/spot_light/vert.shader", "../shaders/spot_light/frag.shader");
        
        opengl::matrix4f projection;
        opengl::matrix4f view;
        glm::mat4 view_glm;
        opengl::matrix4f model;

        opengl::camera cam(window);

        float prevFrame = 0.0f;
        float currentFrame = 0.0f;
        glEnable(GL_DEPTH_TEST);

        opengl::Light default_light = {
            .ambient = opengl::vec3(0.8, 0.8, 0.8),
            .diffuse = opengl::vec3(1.0, 1.0, 1.0),
            .specular = opengl::vec3(1.0, 1.0, 1.0),    // light's diffuse and specular should be the same
            .position = opengl::vec3(0.0, 0.0, -8.0),
            .direction = opengl::vec3(0.0, 0.0, 1.0),
            .outerCutoff = std::cos (opengl::degrees_to_radians(20)),
            .innerCutoff = std::cos(opengl::degrees_to_radians(12.5)), .constant = 1.0f, .linear = 0.09f, .quadratic = 0.032f,
            .type = opengl::DIRECTIONAL
        };
        opengl::shader currentLightShader = baseShader;
        if( default_light.type == opengl::DIRECTIONAL)
            currentLightShader = directionlLightShader;
        else if( default_light.type == opengl::POINT)
            currentLightShader = pointLightShader;
        else if( default_light.type == opengl::SPOT)
            currentLightShader = spotlLightShader;
        while (!glfwWindowShouldClose(window)) {

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            currentFrame = (float)glfwGetTime();
            float delta = currentFrame - prevFrame;
            prevFrame = currentFrame;

//          -------------------- Render -------------------
            projection = opengl::perspective(opengl::degrees_to_radians(cam.getFOV()), 800.0f/600.0f, 0.1f, 100.0f);
            
            cam.init(delta, io);
            cam.focus();
            view_glm = cam.lookAt_glm();

            currentLightShader.use();
            currentLightShader.setMatrix4f("model", model);
            currentLightShader.setMatrix4f("view", view_glm);
            currentLightShader.setMatrix4f("projection", projection);
            currentLightShader.setVec3("lookPos", cam.getPosition());
            currentLightShader.setLight("default_light", default_light);
            backpack.Draw(currentLightShader);
            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

                ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

                if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                ImGui::End();
            }

            // multiple cubes
            // for(int i = 0; i < 10; i++) {
            //     opengl::matrix4f cubesModel;
            //     opengl::translate(cubesModel, cubePositions[i]);
            //     float angle = 20.0f * static_cast<float>(i);
            //     opengl::rotate(cubesModel, angle, cubePositions[i]);
            //     baseShader.setMatrix4f("model", cubesModel);
            //     glDrawArrays(GL_TRIANGLES, 0, 36); 
            // }

            if (default_light.type == opengl::SPOT) { // only for flashlight effect. Otherwise pair it with the light source cube
                    default_light.position = cam.getPosition();
                    default_light.direction = cam.getTarget();
            }
            if(default_light.type == opengl::POINT) {
                // light source
                // float radius = 20.0f;
                // opengl::vec3 translator((delta * sin(currentFrame) * radius), 0.0f, (delta * cos(currentFrame) * radius));
                // default_light.position = default_light.position + translator;
                // lightSourceShader.use();
                // lightSourceShader.setMatrix4f("model", newModel);
                // lightSourceShader.setMatrix4f("view", view_glm);
                // lightSourceShader.setMatrix4f("projection", projection);
                // glDrawArrays(GL_TRIANGLES, 0, 36); 
            }

//          -----------------------------------------------

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
