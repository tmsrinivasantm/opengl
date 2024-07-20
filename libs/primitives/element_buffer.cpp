#include <primitives/element_buffer.hpp>
namespace opengl {
element_buffer::element_buffer() {
    glGenBuffers(1, &identifier);
}
element_buffer::~element_buffer() {
    glDeleteBuffers(1, &identifier);
}
void element_buffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, identifier);
}
void element_buffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void element_buffer::setData(unsigned int data[], int size){
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
};
