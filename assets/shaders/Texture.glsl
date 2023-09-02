#type vertex
#version 460 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

layout(std140, binding = 0) uniform Matrices
{
    mat4 u_Projection;
	mat4 u_View;
};
uniform mat4 u_Transform;

out vec2 v_TexCoord;

void main()
{
	v_TexCoord = a_TexCoord;
	gl_Position =  u_Projection * u_View * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 460 core
		
in vec2 v_TexCoord;
out vec4 color;

uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	//if(texColor.a < 0.1)
	//	discard;
	color = texColor;
}