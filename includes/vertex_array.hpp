#pragma once
#include <glad/glad.h>
namespace opengl {
class vertex_array {
public:
    vertex_array();
    void bind();
    void unbind();
private:
    unsigned int identifier;
};
}; // namespace opengl
