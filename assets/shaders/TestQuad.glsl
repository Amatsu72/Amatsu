#type vertex
#version 460 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

void main()
{
	gl_Position = vec4(a_Position, 1.0);
	v_TexCoord = a_TexCoord;
}

#type fragment
#version 460 core	
out vec4 color;

in vec2 v_TexCoord;
uniform sampler2D u_DepthMap;
uniform float u_near;
uniform float u_far;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * u_near * u_far) / (u_far + u_near - z * (u_far - u_near));	
}

void main()
{
	float depthValue = texture(u_DepthMap, v_TexCoord).r;
	//color = vec4(vec3(LinearizeDepth(depthValue) / u_far), 1.0); // perspective
	color = vec4(vec3(depthValue), 1.0); // orthographic
	
}