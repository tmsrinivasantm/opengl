#include <array_buffers.hpp>
namespace opengl {
array_buffer::array_buffer(): buffer(GL_ARRAY_BUFFER) {
    glGenBuffers(1, &identifier);
    glBindBuffer(GL_ARRAY_BUFFER, identifier);
}
array_buffer::~array_buffer(){
    glDeleteBuffers(1, &identifier);
}
void array_buffer::bind(){
    glBindBuffer(GL_ARRAY_BUFFER, identifier);
}
void array_buffer::unbind(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
} // namespace opengl
