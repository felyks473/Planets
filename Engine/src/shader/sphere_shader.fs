#version 330 core

out vec4 aColor;
in vec2 TexCoord;

uniform sampler2D Texture;

void main()
{
    aColor = texture(Texture, TexCoord);
}
