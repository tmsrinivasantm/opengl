#pragma once
#include <glad/glad.h>
#include <iostream>
#include <deps/stb_image.h>
namespace opengl {
class texture {
public:
    texture(const std::string &filepath);
    ~texture();
    void bind();
    void unbind();
    void generate(const std::string &filepath);
    unsigned int getIdentifier() { return identifier; }
private:
    unsigned int identifier;
    unsigned char *image_data;
};
} // namespace opengl
