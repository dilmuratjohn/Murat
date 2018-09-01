#shader vertex
#version 330 core

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aNormal;

out vec4 FragPos;
out vec4 Normal;

uniform mat4 model;

uniform mat4 transform;

void main()
{
    gl_Position = transform * aPos;
    FragPos = model * aPos;
    Normal = aNormal;
}


#shader fragment
#version 330 core

in vec4 FragPos;
in vec4 Normal;

out vec4 FragColor;

uniform vec4 lightPos;
uniform vec4 objectColor;
uniform vec4 lightColor;

void main()
{
    float ambientStrength = 0.1f;
    vec4 ambient = ambientStrength * lightColor;

    vec4 norm = normalize(Normal);
    vec4 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * lightColor;
    FragColor = (ambient + diffuse) * objectColor;

}