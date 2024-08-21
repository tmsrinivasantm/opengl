#pragma once
#include <glad/glad.h>
#include <iostream>
#include <deps/stb_image.h>
namespace opengl {
class Texture {
public:
    Texture(const std::string &filepath, const unsigned int type);
    ~Texture();
    void bind();
    void unbind();
    void generate();
    unsigned int getIdentifier() { return identifier; }
    std::string getPath() { return filePath; }
    unsigned int getType() { return type; }
private:
    unsigned int identifier;
    unsigned char *image_data;
    unsigned int type;
    std::string filePath;
};
} // namespace opengl
