#version 330 core
out vec4 FragColor;

in VS_OUT {
	vec3 FragPos;  
	vec3 Normal;  
} fs_in;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float lightPower;

float shininess = 32.0f;
vec3 baseColor = vec3(0.6, 0.6, 0.6);
vec3 specularColor = vec3(1, 1, 1);

void main()
{
    // ambient
    vec3 ambient = 0.2f * baseColor;
  	
    // diffuse 
    vec3 norm = normalize(fs_in.Normal);
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightColor * diff * baseColor;  
    
    // specular
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = lightColor * (spec * specularColor);  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 