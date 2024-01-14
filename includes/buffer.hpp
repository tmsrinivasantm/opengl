#pragma once
#include <glad/glad.h>
namespace opengl {
class buffer {
public:
    buffer(unsigned int type);
    ~buffer();
    void bind(unsigned int type);
    void unbind();
    void setData(float data[], int size);
private:
    unsigned int identifier;
    unsigned int type;
};
}; // namespace opengl
