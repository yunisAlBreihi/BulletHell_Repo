#version 440 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;
uniform mat4 vp;
out vec2 TexCoord;

in RectInfo{
   vec2 data;
} RectIn[];

void main()
{
    float spriteWidth = RectIn[0].data.x;
    float spriteHeight = RectIn[0].data.y;
    
    //left top rendering
    gl_Position = vp *(gl_in[0].gl_Position + (vec4(0, 0, 0, 0)));
    TexCoord = vec2(0, 0);
    EmitVertex();

    gl_Position =  vp *(gl_in[0].gl_Position + (vec4(spriteWidth, 0, 0, 0)));
    TexCoord = vec2(1, 0);
    EmitVertex();

    gl_Position = vp *(gl_in[0].gl_Position + (vec4(0, spriteHeight, 0, 0)));
    TexCoord = vec2(0, 1);
    EmitVertex();

    gl_Position = vp *(gl_in[0].gl_Position +  (vec4(spriteWidth, spriteHeight, 0, 0)));
    TexCoord = vec2(1, 1);
    EmitVertex();
}