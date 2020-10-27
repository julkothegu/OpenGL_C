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
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
    float cutoff;
    float outercut;
};
  
uniform vec3 viewPos;
uniform Material mat;
uniform Light light;

in vec3 fragPos;
in vec3 Normal; 
in vec2 Tex;

void main()
{   
    vec3 lightDir = normalize(light.position - fragPos);

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - fragPos);    
    vec3 reflectDir = reflect(-lightDir, norm);

    float distance = length(light.position - fragPos);
    float atten = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.shininess);
    vec3 specular = light.specular * spec * texture(mat.specular, Tex).rgb;

    vec3 ambient = light.ambient * texture(mat.diffuse, Tex).rgb;
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(mat.diffuse, Tex).rgb;

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutoff - light.outercut;
    float intensity = clamp((theta - light.outercut) / epsilon, 0.0, 1.0);

    ambient *= intensity;
    diffuse *= intensity;
    specular *= intensity;

    vec3 result = (ambient*atten) + (diffuse*atten) + (specular*atten);
    FragColor = vec4(result, 1.0);
    
}