#shader vertex
#version 330 core
layout (location = 0) in vec4 Position;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    gl_Position = u_projection * u_view * u_model * Position;
}

#shader fragment
#version 330 core

out vec4 Color;

void main()
{
    Color = vec4(1.0);
}