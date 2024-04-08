#include <cube.hpp>
namespace opengl {
cube::cube(shader cubeShader): cubeShader(cubeShader) {
    vbo.setData(vertices, sizeof(vertices));
    vbo.bind();
    vao.bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    this->cubeShader.use();
    this->cubeShader.setMatrix4f("model", model);
    draw();
}
}
