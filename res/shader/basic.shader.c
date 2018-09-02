#shader vertex
#version 330 core
layout (location = 0) in vec4 Position;
layout (location = 1) in vec4 Color;
layout (location = 2) in vec2 TexCoord;
layout (location = 3) in vec4 Normal;


out vec4 v_Color;
out vec2 v_TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;



void main()
{
    gl_Position = projection * view * model * Position;
    v_Color = Color;
    v_TexCoord = TexCoord;
}

#shader fragment
#version 330 core

out vec4 Color;

in vec4 v_Color;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;


void main()
{
    Color = texture(u_Texture, v_TexCoord);
}