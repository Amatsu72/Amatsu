#type vertex
#version 460 core
layout(location = 0) in vec3 a_Position;

out vec3 v_TexCoord;

layout(std140, binding = 0) uniform Matrices
{
    mat4 u_Projection;
	mat4 u_View;
};
uniform mat4 u_Transform;

void main()
{
    v_TexCoord = a_Position;
    vec4 pos = u_Projection * u_View * u_Transform * vec4(a_Position, 1.0);
    gl_Position = pos.xyww;
}

#type fragment
#version 460 core
out vec4 color;

in vec3 v_TexCoord;

uniform samplerCube u_Skybox;

void main()
{    
    color = texture(u_Skybox, v_TexCoord);
}