#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

struct Material {
    vec3 specular;
    vec3 ambient;
    vec3 diffuse;
    float shininess;
};

struct Light {
    vec3 ambient;
    vec3 specular;
    vec3 diffuse;
    vec3 position;
};

uniform vec3 objectColor;
uniform vec3 lookPos;
uniform Material material;
uniform Light default_light;
uniform vec3 lightColour;

void main()
{
    // calculate ambient lighting
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * material.ambient * default_light.ambient;

    // calculate diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(default_light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = default_light.diffuse * (diff * material.diffuse);
    
    // calculate specular lighting
    float specularStrength = 0.5;
    vec3 lookDir = normalize(lookPos - FragPos);
    vec3 reflectDir = normalize(reflect(-lightDir, norm));
    float spec = pow(max(dot(lookDir, reflectDir), 0.0), material.shininess);
    vec3 specular = default_light.specular * (material.specular * spec);

    // calculate final lighting
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result,1.0);
}
