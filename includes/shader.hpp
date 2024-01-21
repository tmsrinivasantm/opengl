#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
namespace opengl {
class shader{
public:
    shader(const std::string &vertFilepath, const std::string &fragFilepath);
    ~shader();
    void link();
    void use();
    void setVertShader(const std::string &vertFilepath);
    void setFragShader(const std::string &fragFilepath);

    inline unsigned int getIdentifier() { return identifier; }
    void setMatrix4f(const char *uniformName, glm::mat4 &matrix);
private:
    unsigned int identifier;
    int vertexShader, fragmentShader;
};
}
