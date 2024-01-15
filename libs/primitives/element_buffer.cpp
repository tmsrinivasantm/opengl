#include <element_buffer.hpp>
namespace opengl {
element_buffer::element_buffer() {
    glGenBuffers(1, &identifier);
    bind();
}
void element_buffer::bind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, identifier);
}
void element_buffer::unbind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void element_buffer::setData(unsigned int data[], int size){
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
};
