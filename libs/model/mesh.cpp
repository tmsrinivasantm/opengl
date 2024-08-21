#include "opengl.hpp"
#include <model/mesh.hpp>
namespace opengl {
Mesh::Mesh(std::vector<vertex> vertices, std::vector<unsigned int> indices,
           std::vector<texture_metadata> textures) {

    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setupMesh();
}
void Mesh::setupMesh() {
    VAO.bind();
    VBO.bind();

    VBO.setData(&vertices[0], vertices.size() * sizeof(vertex));

    EBO.bind();
    EBO.setData(&indices[0],indices.size() * sizeof(unsigned int));

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex),
                          (void *)offsetof(vertex, Normals));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex),
                          (void *)offsetof(vertex, TexCoords));

    VAO.unbind();
}
void Mesh::Draw(shader &shader) {
    Material backpack_material;
    for (unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
        if (textures[i].type == DIFFUSE) {
            backpack_material.diffuse = i;
        } else if (textures[i].type == SPECULAR) {
            backpack_material.specular = i;
        }
    }
    backpack_material.shininess = 32.0f;
    shader.setMaterial("material", backpack_material);

    // draw mesh
    VAO.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    VAO.unbind();
}
}; // namespace opengl
