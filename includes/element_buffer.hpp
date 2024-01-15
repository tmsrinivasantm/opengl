#pragma once
#include <glad/glad.h>
#include <iostream>
namespace opengl {
class element_buffer{ 
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
