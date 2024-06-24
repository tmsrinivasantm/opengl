#include <primitives/array_buffers.hpp>
namespace opengl {
array_buffer::array_buffer() {
    glGenBuffers(1, &identifier);
    bind();
}
array_buffer::~array_buffer() {
    glDeleteBuffers(1, &identifier);
}
void array_buffer::unbind(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void array_buffer::setData(const float data[], int size){
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
void array_buffer::setData(const vertex data[], int size) {
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
void array_buffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, identifier);
}

} // namespace opengl
