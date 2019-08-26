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

struct Material
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

struct Light
{
    vec4 position;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

out vec4 Color;

in vec4 v_Color;
in vec2 v_TexCoord;
in vec4 v_Normal;
in vec4 v_FragPosition;


uniform sampler2D u_Texture;
uniform vec4 u_viewPosition;
uniform Material u_material;
uniform Light u_light;



void main()
{
    vec4 ambient = u_light.ambient * u_material.ambient;

    vec4 diffuse = u_light.diffuse * (max(
                                          dot(
                                                  normalize(v_Normal), normalize(u_light.position - v_FragPosition)),
                                          0.0)
                                      * u_material.diffuse);

    vec4 specular = u_light.specular * (pow(
                                            max(
                                                    dot(
                                                            normalize(u_viewPosition - v_FragPosition),
                                                            reflect(normalize(v_FragPosition - u_light.position),
                                                                    normalize(v_Normal)
                                                                   )
                                                    ),
                                                    0.0),
                                            u_material.shininess)
                                        * u_material.specular);

    Color = (ambient + diffuse + specular) * texture(u_Texture, v_TexCoord);
}










