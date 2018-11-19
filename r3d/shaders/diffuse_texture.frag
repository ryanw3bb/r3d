#version 330 core
out vec4 FragColor;

in VS_OUT {
	vec3 FragPos;  
	vec3 Normal;  
	vec2 TexCoords;
} fs_in;

uniform sampler2D diffuseSampler;
uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float lightPower;

float shininess = 32.0f;
vec3 specularColor = vec3(1, 1, 1);

void main()
{
    // ambient
    vec3 ambient = 0.2f * texture(diffuseSampler, fs_in.TexCoords).rgb;
  	
    // diffuse 
    vec3 norm = normalize(fs_in.Normal);
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightColor * diff * texture(diffuseSampler, fs_in.TexCoords).rgb;  
    
    // specular
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = lightColor * (spec * specularColor);  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 