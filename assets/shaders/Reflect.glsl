#type vertex
#version 460 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

layout(std140, binding = 0) uniform Matrices
{
    mat4 u_Projection;
	mat4 u_View;
};
uniform mat4 u_Transform;

out vec3 v_Normal;
out vec3 v_Position;

void main()
{
	v_Normal = mat3(transpose(inverse(u_Transform))) * a_Normal;
    v_Position = vec3(u_Transform * vec4(a_Position, 1.0));
	gl_Position = u_Projection * u_View * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 460 core
out vec4 color;	

in vec3 v_Normal;
in vec3 v_Position;

uniform vec3 u_CameraPosition;
uniform samplerCube u_Skybox;

vec3 my_reflect();
vec3 my_refract();

void main()
{
    //vec3 R = my_reflect();
    vec3 R = my_refract();
    color = vec4(texture(u_Skybox, R).rgb, 1.0);
}

vec3 my_reflect()
{
    vec3 I = normalize(v_Position - u_CameraPosition);
    vec3 R = reflect(I, normalize(v_Normal));
    return R;
}
vec3 my_refract()
{
    float ratio = 1.00 / 1.52;
    vec3 I = normalize(v_Position - u_CameraPosition);
    vec3 R = refract(I, normalize(v_Normal), ratio);
    return R;
}