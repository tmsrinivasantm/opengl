#pragma once
#include <glad/glad.h>
#include <buffer.hpp>
namespace opengl {
class array_buffer: public buffer {
public:
    array_buffer();
    ~array_buffer();
    void bind();
    void unbind();
private:
    unsigned int identifier;
};
}; // namespace opengl
