#shader vertex
#version 330 core
layout (location = 0) in vec4 Position;
layout (location = 1) in vec3 Color;
layout (location = 2) in vec2 TexCoord;

out vec3 u_Color;
out vec2 v_TexCoord;

uniform mat4 transform;


void main()
{
    gl_Position = transform * Position;
    u_Color = Color;
    v_TexCoord = TexCoord;
}

#shader fragment
#version 330 core

out vec4 Color;

in vec3 u_Color;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;


void main()
{
    Color = texture(u_Texture, v_TexCoord);
}