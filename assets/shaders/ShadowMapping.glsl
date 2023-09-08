#type vertex
#version 460 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

uniform mat4 u_Transform;
uniform mat4 u_LightSpace;
uniform mat4 u_Projection;
uniform	mat4 u_View;

out VS_OUT {
	vec2 TexCoord;
	vec3 Normal;
	vec3 FragPos;
	vec4 FragPosLightSpace;
} v_out;

void main()
{
	v_out.TexCoord = a_TexCoord;
	gl_Position = u_Projection * u_View * u_Transform * vec4(a_Position, 1.0);
	v_out.Normal = mat3(transpose(inverse(u_Transform))) * a_Normal; 
	v_out.FragPos = vec3(u_Transform * vec4(a_Position, 1.0));
	v_out.FragPosLightSpace = u_LightSpace * vec4(v_out.FragPos, 1.0);
}

#type fragment
#version 460 core
out vec4 color;	

in VS_OUT {
	vec2 TexCoord;
	vec3 Normal;
	vec3 FragPos;
	vec4 FragPosLightSpace;
} v_in;

uniform sampler2D u_Texture;
uniform sampler2D u_ShadowMap;
uniform vec3 u_ViewPosition;
uniform vec3 u_LightPos;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    projCoords = projCoords * 0.5 + 0.5;

    float closestDepth = texture(u_ShadowMap, projCoords.xy).r; 

    float currentDepth = projCoords.z;

    vec3 normal = normalize(v_in.Normal);
    vec3 lightDir = normalize(u_LightPos - v_in.FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(u_ShadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(u_ShadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;

    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}

void main()
{
	vec3 diffuse_color = texture(u_Texture, v_in.TexCoord).rgb;
    vec3 normal = normalize(v_in.Normal);
    vec3 lightColor = vec3(0.3);
    // ambient
    vec3 ambient = 0.3 * lightColor;
    // diffuse
    vec3 lightDir = normalize(u_LightPos - v_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse =  diff * lightColor;
    // specular
    vec3 viewDir = normalize(u_ViewPosition - v_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular =  spec * lightColor;    
    // calculate shadow
    float shadow = ShadowCalculation(v_in.FragPosLightSpace);                      
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * diffuse_color;   
	
	color = vec4(lighting, 1.0);
}

