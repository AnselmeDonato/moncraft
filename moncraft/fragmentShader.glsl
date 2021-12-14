#version 330 core
in vec2 TexCoord;
in vec3 FragPos; 
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D _texture;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos; 

void main()
{
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    vec3 result = (ambient+diffuse) * objectColor;
    
    FragColor = vec4(result, 1.0);
    //FragColor = texture(_texture, TexCoord) * vec4(lightColor * objectColor, 1.0);
}
