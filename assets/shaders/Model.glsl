#type vertex
#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 v_TexCoord;
out vec3 v_Normal;

void main()
{
	v_TexCoord = a_TexCoord;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
	//v_Normal = mat3(transpose(inverse(u_Transform))) * a_Normal; 
}

#type fragment
#version 330 core
		
in vec2 v_TexCoord;
out vec4 color;

struct Material{
	sampler2D diffuse;
	sampler2D specular;
};
uniform Material u_Material;

void main()
{
	color = texture(u_Material.diffuse, v_TexCoord);
}