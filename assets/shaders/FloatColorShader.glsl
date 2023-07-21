#type vertex
#version 330 core
			
layout(location = 0) in vec3 a_Position;

uniform mat4 u_viewProjection;
uniform mat4 u_transform;

void main()
{
	gl_Position = u_viewProjection * u_transform * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core
		
out vec4 color;
uniform vec4 u_color;

void main()
{
	color = u_color;
}