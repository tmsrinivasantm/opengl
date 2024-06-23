#include <cstring>
#include <primitives/shader.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

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
    shaderString = readFile(filename); shaderSource = shaderString.c_str(); shader = glCreateShader(shaderType);
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
namespace opengl {
shader::shader(const std::string &vertFilepath, const std::string &fragFilepath){
    identifier = glCreateProgram();

    setVertShader(vertFilepath);
    setFragShader(fragFilepath);

    link();
}
void shader::link() {
    glLinkProgram(identifier);
}
void shader::use() {
    glUseProgram(identifier);
}
void shader::setVertShader(const std::string &vertFilePath){
    vertexShader = compileShader(GL_VERTEX_SHADER, vertFilePath);
    glAttachShader(identifier, vertexShader);
}
void shader::setFragShader(const std::string &fragFilepath) {
    fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragFilepath);
    glAttachShader(identifier, fragmentShader);
}
void shader::setMatrix4f(const std::string &uniformName, matrix4f &matrix) {
    glUniformMatrix4fv(glGetUniformLocation(identifier, uniformName.c_str()), 1, GL_FALSE, matrix.getValue());
}
void shader::setMatrix4f(const std::string &uniformName, glm::mat4 &matrix) {
    glUniformMatrix4fv(glGetUniformLocation(identifier, uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}
void shader::setVec3(const std::string &uniformName, const vec3 &vector) {
    glUniform3f(glGetUniformLocation(identifier, uniformName.c_str()), vector[0], vector[1], vector[2]);
}
void shader::setVec3(const std::string &uniformName, glm::vec3 &vector) {
    glUniform3f(glGetUniformLocation(identifier, uniformName.c_str()), vector[0], vector[1], vector[2]);
}
void shader::setFloat(const std::string &uniformName, float num) {
    glUniform1f(glGetUniformLocation(identifier, uniformName.c_str()), num);
}
void shader::setInt(const std::string &uniformName, int num) {
    glUniform1i(glGetUniformLocation(identifier, uniformName.c_str()), num);
}
void shader::setMaterial(const std::string &uniformName, Material material) {
    setInt((uniformName + ".diffuse"), material.diffuse);
    setInt((uniformName + ".specular"), material.specular);
    setFloat((uniformName + ".shininess"), material.shininess);
}
void shader::setLight(const std::string &uniformName, Light light) {
    setVec3((uniformName + ".ambient"), light.ambient);
    setVec3((uniformName + ".diffuse"), light.diffuse);
    setVec3((uniformName + ".specular"), light.specular);
    if (light.type == DIRECTIONAL)
        setVec3((uniformName + ".direction"), light.direction);
    else if (light.type == POINT){
        setVec3((uniformName + ".position"), light.position);
        setFloat((uniformName + ".constant"), light.constant);
        setFloat((uniformName + ".linear"), light.linear);
        setFloat((uniformName + ".quadratic"), light.quadratic);
    }
    else {
        setVec3((uniformName + ".position"), light.position);
        setVec3((uniformName + ".direction"), light.direction);
        setFloat((uniformName + ".outerCutoff"), light.outerCutoff);
        setFloat((uniformName + ".innerCutoff"), light.innerCutoff);
    }
}
shader::~shader() {
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(identifier);
}
}
