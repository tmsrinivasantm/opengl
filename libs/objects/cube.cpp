#include <objects/cube.hpp>
namespace opengl {
cube::cube(shader cubeShader): cubeShader(cubeShader) {
    vbo.setData(vertices, sizeof(vertices));
    vbo.bind();
    vao.bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    this->cubeShader.use();
}
void cube::draw() {
    this->cubeShader.setMatrix4f("model", model);
}
void cube::attachShader(const std::string& vertFilePath, const std::string& fragFilePath) {
    cubeShader = shader(vertFilePath, fragFilePath);
    cubeShader.use();
    cubeShader.setMatrix4f("model", model);
}
void cube::updateModelMatrix(matrix4f& matrix) {
    model = matrix;
    // cubeShader.setMatrix4f("model", model);
}
}
