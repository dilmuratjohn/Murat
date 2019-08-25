#shader vertex
#version 330 core

layout (location = 0) in vec4 a_Position;
layout (location = 1) in vec2 a_TexCoord;

uniform mat4 u_ProjectionView;
uniform mat4 u_Transform;

out vec2 v_TexCoord;

void main()
{
    v_TexCoord = a_TexCoord;
    gl_Position = u_ProjectionView * u_Transform * a_Position;
}

#shader fragment
#version 330 core

in vec2 v_TexCoord;

uniform sampler2D  u_Texture;

out vec4 FragColor;

void main()
{
    FragColor = texture(u_Texture, v_TexCoord);
}
