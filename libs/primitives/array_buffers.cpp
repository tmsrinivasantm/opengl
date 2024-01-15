#include <array_buffers.hpp>
namespace opengl {
array_buffer::array_buffer() {
    glGenBuffers(1, &identifier);
    glBindBuffer(GL_ARRAY_BUFFER, identifier);
}
array_buffer::~array_buffer() {
    glDeleteBuffers(1, &identifier);
}
void array_buffer::unbind(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void array_buffer::setData(float data[], int size){
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

} // namespace opengl
