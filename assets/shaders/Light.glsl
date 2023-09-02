#type vertex
#version 460 core
			
layout(location = 0) in vec3 a_Position;

uniform mat4 u_Transform;

layout(std140, binding = 0) uniform Matrices
{
    mat4 u_Projection;
	mat4 u_View;
};

void main()
{
	gl_Position = u_Projection * u_View * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 460 core
		
out vec4 color;
uniform vec4 u_color;

void main()
{
	color = u_color;
}