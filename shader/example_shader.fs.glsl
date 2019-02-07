#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_color;

void main()
{
    if(gl_FrontFacing)
        color = u_color;
    else
        color = vec4(1.0 - u_color.x, 1.0 - u_color.y, 1.0 - u_color.z, 1.0 - u_color.w);
}
