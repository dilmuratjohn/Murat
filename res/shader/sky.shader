#shader vertex
#version 330 core

layout (location = 0) in vec4 aPos;

out vec4 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = aPos;
    vec4 pos = projection * view * aPos;
    gl_Position = pos.xyww;
}


#shader fragment
#version 330 core

out vec4 FragColor;

in vec4 TexCoords;

uniform samplerCube skybox;

void main()
{
    FragColor = texture(skybox, TexCoords);
}