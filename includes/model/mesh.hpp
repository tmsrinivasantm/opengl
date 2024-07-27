#pragma once
#include <deps/stb_image.h>
#include <glad/glad.h>
#include <math/vector.hpp>
#include <primitives/shader.hpp>
#include <vector>
namespace opengl {
struct texture_metadata {
    unsigned int id;
    unsigned int type;
    std::string path;
    unsigned char *image_data;
};
class Mesh {
  public:
    Mesh(std::vector<vertex> vertices, std::vector<unsigned int> indices,
         std::vector<texture_metadata> textures);
    void Draw(shader &shader);

  private:
    void setupMesh();
    unsigned int VAO, VBO, EBO;
    std::vector<vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<texture_metadata> textures;
};
}; // namespace opengl
