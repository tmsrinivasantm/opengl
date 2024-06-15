#pragma once
#include <glad/glad.h>
#include <math/matrices.hpp>
#include <math/vector.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <opengl.hpp>
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
    void setMatrix4f(const std::string &uniformName, matrix4f &matrix);
    void setMatrix4f(const std::string &uniformName, glm::mat4 &matrix);
    void setVec3(const std::string &uniformName, const vec3 &vector);
    void setVec3(const std::string &uniformName, glm::vec3 &vector);
    void setMaterial(const std::string &uniformName, Material material);
    void setFloat(const std::string &uniformName, float num);
    void setLight(const std::string &uniformName, Light light);
private:
    unsigned int identifier;
    int vertexShader, fragmentShader;
};
}
