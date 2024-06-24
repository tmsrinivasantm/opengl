#pragma once
#include <glad/glad.h>
#include <iostream>
#include <opengl.hpp>
namespace opengl {
class array_buffer {
public:
    array_buffer();
    ~array_buffer();
    void bind();
    void unbind();
    void setData(const float data[], int size);
    void setData(const vertex data[], int size);
private:
    unsigned int identifier;
};
}; // namespace opengl
