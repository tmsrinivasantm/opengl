#pragma once
#include <buffer.hpp>
#include <glad/glad.h>
namespace opengl {
class element_buffer : public buffer{
public:
    element_buffer();
    ~element_buffer();
    void bind();
    void unbind();
    void setData(unsigned int data[], int size);
private:
    unsigned int identifier;
};
}; // namespace opengl
