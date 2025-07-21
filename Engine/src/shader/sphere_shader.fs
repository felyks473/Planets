#version 330 core

out vec4 aColor;
in vec2 TexCoord;

uniform sampler2D Texture0;
uniform sampler2D Texture1;

uniform int state;

void main()
{
    vec4 texColor0 = texture(Texture0, TexCoord);
    vec4 texColor1 = texture(Texture1, TexCoord);
    
    if (state == 1)
    {
        aColor = texColor0 + texColor1;
    }
    else
    {
        aColor = texColor0;
    }
}
