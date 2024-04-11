#pragma once
#include <glad/glad.h>
#include <math/matrices.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
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
    void setMatrix4f(const char *uniformName, matrix4f &matrix);
private:
    unsigned int identifier;
    int vertexShader, fragmentShader;
};
}
