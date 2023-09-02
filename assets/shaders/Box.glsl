#type vertex
#version 460 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

uniform mat4 u_Transform;

layout(std140, binding = 0) uniform Matrices
{
    mat4 u_Projection;
	mat4 u_View;
};

out vec2 v_TexCoord;
out vec3 v_Normal;

void main()
{
	v_Normal = mat3(transpose(inverse(u_Transform))) * a_Normal;
	v_TexCoord = a_TexCoord;
	gl_Position = u_Projection * u_View * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 460 core
out vec4 color;	

in vec2 v_TexCoord;
in vec3 v_Normal;

uniform sampler2D u_Texture;

void main()
{
	color = texture(u_Texture, v_TexCoord);
}