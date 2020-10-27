#version 330 core

out vec4 FragColor;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;
    sampler2D height;
    float shininess; 
};

struct DirLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 color;

    float constant;
    float linear;
    float quadratic;
};

in vec2 TexPos;
in vec3 Color;
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 cameraPos;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform DirLight DirLights;
uniform Material material;
uniform PointLight pointLight;

uniform samplerCube skybox;

float near = 0.1;
float far = 100.0;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcNewPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

float linearDepth(float depth);

void main()
{
    float ratio = 1.00 / 1.52;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 Normalized = normalize(Normal);

    vec3 I = normalize(FragPos - cameraPos);
    vec3 R = refract(I, normalize(Normal), ratio);

    // now for every individual mesh instead of all of them

    vec3 result = CalcNewPointLight(pointLight, Normalized, FragPos, viewDir);

    //float depth = linearDepth(gl_FragCoord.z) / far;
	
    FragColor = vec4(result, 1.0);

	//FragColor = vec4(vec3(depth), 1.0);
}

float linearDepth(float depth)
{
    float z =   depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * texture(material.diffuse, TexPos).rgb;
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexPos).rgb;
    vec3 specular = light.specular * spec * texture(material.diffuse, TexPos).rgb;
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexPos));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexPos));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexPos));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 CalcNewPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 halfwayDir = normalize(lightDir + viewDir);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexPos));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexPos));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexPos));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 calcSimplePoint(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * vec3(texture(material.diffuse, TexPos));

    vec3 halfwayDir = normalize(lightDir + viewDir);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * vec3(texture(material.specular, TexPos));
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0/ distance * distance;
    // combine results

    diffuse *= attenuation;
    specular *= attenuation;
   
    return diffuse + specular;    
}