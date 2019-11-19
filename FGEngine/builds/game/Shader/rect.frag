#version 440 core
uniform float border_width;
uniform float aspect;
in vec2 TexCoord;
in vec4 Fill;
in vec4 Border;
out vec4 frag_color;

void main() 
{
    float maxX = 1.0 - 0.05;
    float minX = 0.05;
    float maxY = maxX / 1.0;
    float minY = minX / 1.0;

    if (TexCoord.x < maxX && TexCoord.x > minX  && TexCoord.y < maxY && TexCoord.y > minY) 
    {
        frag_color = Fill;
    } 
    else 
    {
        frag_color = Border;
    }
}