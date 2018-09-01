#shader vertex
#version 330 core

layout (location = 0) in vec4 aPos;

uniform mat4 transform;

void main()
{
    gl_Position = transform * aPos;
}


#shader fragment
#version 330 core

out vec4 FragColor;
uniform vec4 objectColor;
uniform vec4 lightColor;

void main()
{
    FragColor = vec4(lightColor * objectColor);
}