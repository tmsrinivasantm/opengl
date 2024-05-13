#include <primitives/shader.hpp>
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
void shader::setMatrix4f(const char *uniformName, matrix4f &matrix) {
    glUniformMatrix4fv(glGetUniformLocation(identifier, uniformName), 1, GL_FALSE, matrix.getValue());
}
void shader::setVec3(const char *uniforName, const vec3 &vector) {
    glUniform3f(glGetUniformLocation(identifier, uniforName), vector[0], vector[1], vector[2]);
}

shader::~shader() {
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(identifier);
}
}
