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
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex),
                 &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);

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

    glBindVertexArray(0);
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
    // glActiveTexture(GL_TEXTURE0);

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
}; // namespace opengl
