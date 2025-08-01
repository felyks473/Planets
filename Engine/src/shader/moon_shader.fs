#version 330 core

out vec4 aColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D Texture;

void main()
{
    vec4 tex = texture(Texture, TexCoord);

    vec3 norm = normalize(Normal);
    vec3 lightPos = vec3(0.0);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = dot(norm, lightDir);

    if (diff > 0.0)
        aColor = tex;
    else
        aColor = tex * 0.08; // To simulate the far side of the moon
}
