#pragma once
#include <glad/glad.h>
namespace opengl {
class vertex_array {
public:
    vertex_array();
    ~vertex_array();
    void bind() const;
    void unbind() const;
private:
    unsigned int identifier;
};
}; // namespace opengl
