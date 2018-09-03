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
    v_Normal = (transpose(inverse(model))) * Normal;
}

#shader fragment
#version 330 core

out vec4 Color;

in vec4 v_Color;
in vec2 v_TexCoord;
in vec4 v_Normal;
in vec4 v_FragPosition;


uniform sampler2D u_Texture;
uniform vec4 u_lightPosition;
uniform vec4 u_lightColor;
uniform vec4 u_viewPosition;


void main()
{
    vec4 diffuse = max(
                       dot(
                           normalize(v_Normal), normalize(u_lightPosition - v_FragPosition)),
                       0.0) *  u_lightColor;
    vec4 ambient = 0.1 * u_lightColor;
    vec4 specular = 0.5 * u_lightColor *
                    pow(
                        max(
                            dot(
                                normalize(u_viewPosition - v_FragPosition),
                                reflect(normalize(v_FragPosition - u_lightPosition),
                                        normalize(v_Normal)
                                       )
                            ),
                            0.0),
                        32);
    Color = (ambient + diffuse + specular) * texture(u_Texture, v_TexCoord);
}










