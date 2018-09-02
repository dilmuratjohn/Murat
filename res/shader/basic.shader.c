#shader vertex
#version 330 core
layout (location = 0) in vec4 Position;
layout (location = 1) in vec4 Color;
layout (location = 2) in vec2 TexCoord;
layout (location = 3) in vec4 Normal;


out vec4 v_Color;
out vec2 v_TexCoord;
out vec4 v_Normal;
out vec4 v_FragPosition;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;




void main()
{
    gl_Position = projection * view * model * Position;
    v_FragPosition = model * Position;
    v_Color = Color;
    v_TexCoord = TexCoord;
    v_Normal = Normal;
}

#shader fragment
#version 330 core

out vec4 Color;

in vec4 v_Color;
in vec2 v_TexCoord;
in vec4 v_Normal;
in vec4 v_FragPosition;


uniform sampler2D u_Texture;
uniform vec4 lightPosition;


void main()
{
    Color = (0.1 * vec4(1.0) + max(dot(normalize(v_Normal), normalize(lightPosition - v_FragPosition)), 0.0) * vec4(1.0)) * texture(u_Texture, v_TexCoord);
}










