#pragma once
#include <primitives/texture.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <primitives/shader.hpp>
#include <model/mesh.hpp>
#include <vector>
namespace opengl {
class Model {
  public:
    Model(const std::string &path);
    ~Model();
    void Draw(shader &shader);
  private:
    std::vector<Mesh*> meshes;
    std::vector<Texture*> textures_loaded;
    std::string directory;
    void loadModel(const std::string &path);
    void processNode(const aiScene *scene, aiNode *node);
    Mesh* processMesh(const aiScene *scene, aiMesh *mesh);
    std::vector<texture_metadata> loadTextures(aiMaterial *material, aiTextureType type, unsigned int typeName);
};
} // namespace opengl
