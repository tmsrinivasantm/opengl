#version 330 core
out vec4 FragColor;

in vec3 finalColour;
in vec2 texture_coords;
uniform sampler2D texture_image;

void main()
{
    FragColor = texture(texture_image, texture_coords);
}
