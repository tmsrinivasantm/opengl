#include <buffer.hpp>
namespace opengl {
buffer::buffer(unsigned int type): type(type) {
    glGenBuffers(1, &identifier);
    bind(type);
}
buffer::~buffer(){
    glDeleteBuffers(1, &identifier);
}
void buffer::setData(float data[], int size){
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
void buffer::bind(unsigned int type) {
    glBindBuffer(type, identifier);
}
void buffer::unbind(){
    glBindBuffer(type, 0);
}
} // namespace opengl
