#version 330 core
layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 vcolour;
// layout (location = 2) in vec2 texture;

// out vec3 finalColour;
// out vec2 texture_coords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() 
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}