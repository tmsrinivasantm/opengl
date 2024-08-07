#include <primitives/vertex_array.hpp>

namespace opengl {
vertex_array::vertex_array(){
    glGenVertexArrays(1, &identifier);
}
vertex_array::~vertex_array() {
    glDeleteVertexArrays(1, &identifier);
}
void vertex_array::bind() const {
    glBindVertexArray(identifier);
}
void vertex_array::unbind() const {
    glBindVertexArray(0);
}
}
