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
out vec3 v_FragPos;

void main()
{
	v_TexCoord = a_TexCoord;
	gl_Position = u_Projection * u_View * u_Transform * vec4(a_Position, 1.0);
	v_Normal = mat3(transpose(inverse(u_Transform))) * a_Normal; 
	v_FragPos = vec3(u_Transform * vec4(a_Position, 1.0));
}

#type fragment
#version 460 core
out vec4 color;	

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragPos;

struct DirectionalLight {
	vec3 direction;
	vec3 color;

	float ambient;
	float diffuse;
	float specular;
};
uniform DirectionalLight u_DirectionalLight;

struct PointLight {
	vec3 position;
	vec3 color;

	float ambient;
	float diffuse;
	float specular;

	float constant;
	float linear;
	float quadratic;
};
#define MAX_POINT_LIGHT 4
uniform int u_PointLightCount = 0;
uniform PointLight u_PointLights[MAX_POINT_LIGHT];

struct SpotLight {
	vec3 position;
	vec3 direction;
	vec3 color;

    float ambient;
    float diffuse;
    float specular;

    float constant;
    float linear;
    float quadratic;

	float cutOff;
	float outerCutOff;
};
uniform SpotLight u_SpotLight;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	//sampler2D reflect;

	float shininess;
};
uniform Material u_Material;

uniform vec3 u_ViewPosition;

//uniform samplerCube u_Skybox;

vec3 CalDirLight(DirectionalLight dirLight);
vec3 CalPointLight(PointLight light);
vec3 CalSpotLight(SpotLight light);
//vec3 CalReflect();

vec3 normal = normalize(v_Normal);
vec3 viewDir = normalize(u_ViewPosition - v_FragPos);
vec3 diffuseColor = vec3(texture(u_Material.diffuse, v_TexCoord));
vec3 reflectColor = vec3(texture(u_Material.specular, v_TexCoord));

void main()
{
	vec3 dirColor = CalDirLight(u_DirectionalLight);
	vec3 pointColor;
	for(int i = 0; i < min(u_PointLightCount, MAX_POINT_LIGHT); ++i)
	{
		pointColor += CalPointLight(u_PointLights[i]);
	}
	vec3 spotLight = CalSpotLight(u_SpotLight);
	vec3 emission = vec3(texture(u_Material.emission, v_TexCoord));
	//vec3 reflect = CalReflect();

	vec3 result = dirColor + pointColor + spotLight + emission;
	color = vec4(result, 1.0);
	//color = vec4(vec3(gl_FragCoord.z), 1.0);
}

vec3 CalDirLight(DirectionalLight light)
{
	vec3 lightDir = normalize(-light.direction);
	
	// ambient
	vec3 ambient = light.ambient * light.color * diffuseColor;
	
	// diffuse
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * light.color * diff * diffuseColor;

	// specular
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(viewDir, halfwayDir), 0.0), u_Material.shininess);
	vec3 specular = light.specular * light.color * spec * reflectColor;

	return ambient + diffuse + specular;
}

vec3 CalPointLight(PointLight light)
{
	vec3 lightDir = normalize(light.position - v_FragPos);

	float dist = length(light.position - v_FragPos);
	float attenuation = 1.0 / (
		light.constant + light.linear * dist +  light.quadratic * (dist * dist)
	);

	// ambient
	vec3 ambient = light.ambient * light.color * diffuseColor;
	
	// diffuse
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * light.color * diff * diffuseColor;

	// specular
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(viewDir, halfwayDir), 0.0), u_Material.shininess);
	vec3 specular = light.specular * light.color * spec * reflectColor;

	return (ambient + diffuse + specular) * attenuation;
}

vec3 CalSpotLight(SpotLight light)
{
	vec3 lightDir = normalize(light.position - v_FragPos);

	float dist= length(light.position - v_FragPos);
	float attenuation = 1.0 / (
		light.constant + light.linear * dist +  light.quadratic * (dist * dist)
	);

	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	// ambient
	vec3 ambient = light.ambient * light.color * diffuseColor;
	
	// diffuse
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * light.color * diff * diffuseColor;

	// specular
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(viewDir, halfwayDir), 0.0), u_Material.shininess);
	vec3 specular = light.specular * light.color * spec * reflectColor;

	return (ambient + diffuse + specular) * attenuation * intensity;
}

//vec3 CalReflect()
//{
//	vec3 I = normalize(v_FragPos - u_ViewPosition);
//    vec3 R = reflect(I, normalize(v_Normal));
//	vec3 result = vec3(texture(u_Material.reflect, v_TexCoord)) + texture(u_Skybox,R).rgb;
//	return result;
//}