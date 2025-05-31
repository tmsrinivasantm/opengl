#include <model/model.hpp>
namespace opengl {
Model::Model(const std::string &path) {
    loadModel(path);
}
Model::~Model() {
    for(int i = 0; i < textures_loaded.size(); i++) 
        delete textures_loaded[i];
    for(int i = 0; i < meshes.size(); i++)
        delete meshes[i];
}
void Model::loadModel(const std::string &path) {
    Assimp::Importer import;
    const aiScene *scene =
        import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene, scene->mRootNode);
}
void Model::processNode(const aiScene *scene, aiNode *node) {

    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.emplace_back(processMesh(scene, mesh));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(scene, node->mChildren[i]);
    }
}
Mesh* Model::processMesh(const aiScene *scene, aiMesh *mesh) {
    std::vector<vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<texture_metadata> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        vertex *vertex = new struct vertex();
        vertex->Position = vec3(mesh->mVertices[i].x, mesh->mVertices[i].y,
                               mesh->mVertices[i].z);
        vertex->Normals =
            vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        if (mesh->mTextureCoords[0]) {
            vertex->TexCoords = vec2(mesh->mTextureCoords[0][i].x,
                                    mesh->mTextureCoords[0][i].y);
        } else
            vertex->TexCoords = vec2(0.0f, 0.0f);
        vertices.push_back(*vertex);
        delete vertex;
    }
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<texture_metadata> diffuseMaps =
            loadTextures(material, aiTextureType_DIFFUSE, DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<texture_metadata> specularMaps =
            loadTextures(material, aiTextureType_SPECULAR, SPECULAR);
        textures.insert(textures.end(), specularMaps.begin(),
                        specularMaps.end());
    }

    return  new Mesh(vertices, indices, textures);
}
std::vector<texture_metadata> Model::loadTextures(aiMaterial *material,
                                                  aiTextureType type,
                                                  unsigned int typeName) {
    std::vector<texture_metadata> result;
    int width, height, nrchannels;
    for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {
        aiString str;
        material->GetTexture(type, i, &str);
        texture_metadata texture;
        texture.path = (directory + "/" + str.C_Str());
        bool skip = false;

        for(unsigned int j = 0; j < textures_loaded.size(); j++) {
            if(std::strcmp(textures_loaded[j]->getPath().c_str(), texture.path.c_str()) == 0) {
                result.push_back(texture_metadata{
                    .id = textures_loaded[j]->getIdentifier(),
                    .type = textures_loaded[j]->getType(),
                    .path = textures_loaded[j]->getPath(),
                });
                skip = true; 
                break;
            }
        }

        if (!skip) {
            textures_loaded.push_back(new Texture(texture.path, typeName));
            textures_loaded[textures_loaded.size() - 1]->generate();

            texture.id = textures_loaded[textures_loaded.size() - 1]->getIdentifier();
            texture.type = typeName;
            result.push_back(texture);
        }
    }
    return result;
}
void Model::Draw(shader &shader) {
    for (int i = 0; i < meshes.size(); i++) {
        meshes[i]->Draw(shader);
    }
};
}; // namespace opengl
