#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 vcolour;
layout (location = 2) in vec2 texture;

out vec3 finalColour;
out vec2 texture_coords;

uniform mat4 transform;

void main() 
{
    gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    finalColour = vcolour;
    texture_coords = texture;
}
