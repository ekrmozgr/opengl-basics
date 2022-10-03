#version 330 core

out vec4 fragColor;     

in vec2 texCoord;   

uniform vec4 uColor;

uniform int uTextureFlag;

uniform sampler2D textureMap;   

void main()
{
    fragColor = texture(textureMap, texCoord) * uTextureFlag + uColor;   
}