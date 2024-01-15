#version 330 core
out vec4 FragColor;
in vec3 finalColour;

void main()
{
    FragColor = vec4(finalColour,1.0);
}
