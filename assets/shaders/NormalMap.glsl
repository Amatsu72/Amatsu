#type vertex
#version 460 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;
layout (location = 3) in vec3 a_Tangent;
layout (location = 4) in vec3 a_Bitangent;

out VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
    vec3 Normal;
} v_out;

uniform mat4 u_Transform;
layout(std140, binding = 0) uniform Matrices
{
    mat4 u_Projection;
	mat4 u_View;
};

uniform vec3 u_lightPos;
uniform vec3 u_ViewPosition;

void main()
{
    v_out.FragPos = vec3(u_Transform * vec4(a_Position, 1.0));   
    v_out.TexCoords = a_TexCoord;
    
    mat3 normalMatrix = transpose(inverse(mat3(u_Transform)));
    vec3 T = normalize(normalMatrix * a_Tangent);
    vec3 N = normalize(normalMatrix * a_Normal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    mat3 TBN = transpose(mat3(T, B, N));    
    //v_out.TangentLightPos = TBN * u_lightPos;
    //v_out.TangentViewPos  = TBN * u_ViewPosition;
    //v_out.TangentFragPos  = TBN * v_out.FragPos;
      
    v_out.TangentLightPos =  u_lightPos;
    v_out.TangentViewPos  =  u_ViewPosition;
    v_out.TangentFragPos  =  v_out.FragPos;
    v_out.Normal = mat3(transpose(inverse(u_Transform))) * a_Normal; 

    gl_Position = u_Projection * u_View * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 460 core
out vec4 color;	

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
    vec3 Normal;
} v_in;

struct DirectionalLight {
	vec3 direction;
	vec3 color;

	float ambient;
	float diffuse;
	float specular;
};
uniform DirectionalLight u_DirectionalLight;

uniform sampler2D u_DiffuseMap;
uniform sampler2D u_NormalMap;

void main()
{           

    //vec3 normal = texture(u_NormalMap, v_in.TexCoords).rgb;
    //normal = normalize(normal * 2.0 - 1.0);  // this normal is in tangent space
    vec3 normal = v_in.Normal;
    vec3 diffuse_color = texture(u_DiffuseMap, v_in.TexCoords).rgb;
    // ambient
    vec3 ambient = u_DirectionalLight.ambient * u_DirectionalLight.color * diffuse_color;
    // diffuse
    vec3 lightDir = normalize(v_in.TangentLightPos - v_in.TangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = u_DirectionalLight.diffuse * u_DirectionalLight.color * diff * diffuse_color;
    // specular
    vec3 viewDir = normalize(v_in.TangentViewPos - v_in.TangentFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = u_DirectionalLight.specular * spec * u_DirectionalLight.color;

    color = vec4(ambient + diffuse + specular, 1.0);
}