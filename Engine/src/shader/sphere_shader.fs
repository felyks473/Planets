#version 330 core

out vec4 aColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform sampler2D Texture2;

uniform int state;

void main()
{
    vec4 texColor0 = texture(Texture0, TexCoord); // Day
    vec4 texColor1 = texture(Texture1, TexCoord); // Night
    vec4 texColor2 = texture(Texture2, TexCoord); // Atmosphere

    vec3 norm = normalize(Normal);
    vec3 lightPos = vec3(0.0);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = dot(norm, lightDir); // Without max() because I want to check if it's negative
    if (diff > 0.0)
    {
        if (state == 1)
            aColor = texColor0 + texColor2;
        else
            aColor = texColor0;
    }
    else
    {
        if (state == 1)
            aColor = texColor1 + texColor2 * 0.1; // Make clouds appear less bright when it's night
        else
            aColor = texColor1;
    }
}
