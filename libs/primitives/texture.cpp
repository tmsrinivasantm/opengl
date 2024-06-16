#include <primitives/texture.hpp>

namespace opengl {
texture::texture(const std::string &filepath) {
    glGenTextures(1, &identifier);
    bind();
    stbi_set_flip_vertically_on_load(true);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    generate(filepath);
}
texture::~texture() {
    glDeleteTextures(1, &identifier);
    stbi_image_free(image_data);
}
void texture::bind() { glBindTexture(GL_TEXTURE_2D, identifier); }
void texture::unbind() { glBindTexture(GL_TEXTURE_2D, 0); }
void texture::generate(const std::string &filepath) {

    int width, height, nrchannels;

    image_data = stbi_load(filepath.c_str(), &width, &height, &nrchannels, 0);
    GLenum format;
    if (nrchannels == 1)
        format = GL_RED;
    else if (nrchannels == 3)
        format = GL_RGB;
    else if (nrchannels == 4)
        format = GL_RGBA;
    if (image_data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format,
                     GL_UNSIGNED_BYTE, image_data);
    } else
        std::cout << "FAILED TO LOAD IMAGE " << filepath << std::endl;
}
} // namespace opengl
