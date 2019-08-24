#shader vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

out vec4 v_Color;
void main()
{
    gl_Position = a_Position;
}

#shader fragment
#version 330 core
in vec4 v_Color;
out vec4 Color;

void main()
{
    Color = v_Color;
}