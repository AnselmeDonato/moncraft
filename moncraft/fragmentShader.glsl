#version 330 core
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D _texture;
uniform vec3 objectColor;
uniform vec3 lightColor; 

void main()
{
    FragColor = texture(_texture, TexCoord) * vec4(lightColor * objectColor, 1.0); 
}
