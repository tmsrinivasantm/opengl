#include <vertex_array.hpp>

namespace opengl {
vertex_array::vertex_array(){
    glGenVertexArrays(1, &identifier);
    bind();
}
vertex_array::~vertex_array(){
    glDeleteVertexArrays(1, &identifier);
}
void vertex_array::bind(){
    glBindVertexArray(identifier);
}
void vertex_array::unbind(){
    glBindVertexArray(0);
}
}
