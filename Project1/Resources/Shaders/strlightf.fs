#version 330 core
out vec4 FragColor;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess; 
};

struct Light
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
  
uniform vec3 viewPos;
uniform Material mat;
uniform Light light;

in vec3 fragPos;
in vec3 Normal; 
in vec2 tex;

void main()
{   
    vec3 lightDir = normalize(-light.direction);

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.shininess);
    vec3 specular = light.specular * spec * vec3(texture(mat.specular, tex));

    vec3 ambient = light.ambient * vec3(texture(mat.diffuse, tex));
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse = light.diffuse * diff * vec3(texture(mat.diffuse, tex));
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}