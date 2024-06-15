#pragma once
#include <glad/glad.h>
#include <math/matrices.hpp>
#include <math/vector.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
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
    void setMatrix4f(const char *uniformName, glm::mat4 &matrix);
    void setVec3(const char *uniforName, const vec3 &vector);
    void setVec3(const char *uniforName, glm::vec3 &vector);
private:
    unsigned int identifier;
    int vertexShader, fragmentShader;
};
}
