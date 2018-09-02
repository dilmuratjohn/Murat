#shader vertex
#version 330 core
layout (location = 0) in vec4 l_Position;
layout (location = 1) in vec2 l_TexCoord;
layout (location = 2) in vec4 Normal;

out vec2 v_TexCoord;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    gl_Position = u_projection * u_view * u_model * l_Position;
    v_TexCoord = l_TexCoord;
}

#shader fragment
#version 330 core

out vec4 Color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;


void main()
{
    Color = texture(u_Texture, v_TexCoord);
}