#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
struct Light {
    vec3 ambient;
    vec3 specular;
    vec3 diffuse;
    vec3 direction;
};
uniform vec3 lookPos;
uniform Material material;
uniform Light default_light;

void main()
{
    // calculate ambient lighting
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vec3(texture(material.diffuse, TexCoords));

    // calculate diffuse lighting
    vec3 norm = normalize(Normal);
    // vec3 lightDir = normalize(default_light.position - FragPos);
    vec3 lightDir = normalize(-default_light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = default_light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    
    // calculate specular lighting
    vec3 lookDir = normalize(lookPos - FragPos);
    vec3 reflectDir = normalize(reflect(-lightDir, norm));
    float spec = pow(max(dot(lookDir, reflectDir), 0.0), material.shininess);
    vec3 specular = default_light.specular * texture(material.specular,TexCoords).rgb * spec;

    // calculate final lighting
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result,1.0);
}
