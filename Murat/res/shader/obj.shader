#shader vertex
#version 330 core

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aNormal;

out vec4 FragPos;
out vec4 Normal;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = model * aPos;
    Normal = mat4(transpose(inverse(model))) * aNormal;
    gl_Position = projection * view * FragPos;
}


#shader fragment
#version 330 core

out vec4 FragColor;

in vec4 FragPos;
in vec4 Normal;

uniform vec4 lightPos;
uniform vec4 objectColor;
uniform vec4 lightColor;
uniform vec4 viewPos;

void main()
{
    float ambientStrength = 0.1f;
    vec4 ambient = ambientStrength * lightColor;

    vec4 norm = normalize(Normal);
    vec4 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * lightColor;


    float specularStrength = 0.5;
    vec4 viewDir = normalize(viewPos - FragPos);
    vec4 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    vec4 specular = specularStrength * spec * lightColor;

    FragColor = (ambient + diffuse + specular) * objectColor;

}