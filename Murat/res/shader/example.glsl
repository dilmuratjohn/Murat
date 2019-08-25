#shader vertex
#version 330 core
layout (location = 0) in vec4 a_Position;
uniform mat4 u_ProjectionView;
uniform mat4 u_Transform;
void main()
{
    gl_Position = u_ProjectionView * u_Transform * a_Position;
}

#shader fragment
#version 330 core
out vec4 FragColor;
uniform vec4 u_Color;
void main()
{
    FragColor = u_Color;
}
