#shader vertex
#version 330 core
layout (location = 0) in vec4 Position;
layout (location = 1) in vec4 Normal;
layout (location = 2) in vec2 TexCoord;



out vec2 v_TexCoord;
out vec4 v_Normal;
out vec4 v_FragPosition;


uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;




void main()
{
    gl_Position = u_projection * u_view * u_model * Position;
    v_FragPosition = u_model * Position;
    v_TexCoord = TexCoord;
    v_Normal = (transpose(inverse(u_model))) * Normal;
}

#shader fragment
#version 330 core

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
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


in vec2 v_TexCoord;
in vec4 v_Normal;
in vec4 v_FragPosition;



uniform vec4 u_viewPosition;
uniform Material u_material;
uniform Light u_light;



void main()
{
    vec4 ambient = u_light.ambient
                   * texture(u_material.diffuse, v_TexCoord);

    vec4 diffuse = u_light.diffuse
                   * (max(
                          dot(
                              normalize(v_Normal),
                              normalize(u_light.position - v_FragPosition)),
                          0.0)
                      * texture(u_material.diffuse, v_TexCoord));

    vec4 specular = u_light.specular
                    * (
                        pow(
                            max(
                                dot(
                                    normalize(u_viewPosition - v_FragPosition),
                                    reflect(
                                        normalize(v_FragPosition - u_light.position),
                                        normalize(v_Normal)
                                    )
                                ),
                                0.0),
                            u_material.shininess)
                        * texture(u_material.specular, v_TexCoord));

    vec4 emission = texture(u_material.emission, v_TexCoord);

    Color = ambient + diffuse + specular + emission;
}










