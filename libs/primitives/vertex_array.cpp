#include <vertex_array.hpp>
#include <iostream>

namespace opengl {
vertex_array::vertex_array(){
    glGenVertexArrays(1, &identifier);
    bind();
}
void vertex_array::bind(){
    glBindVertexArray(identifier);
}
void vertex_array::unbind(){
    glBindVertexArray(0);
}
}
