#version 440 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;
uniform mat4 vp;

out vec3 TexCoord;

in TextInfo{
   vec2 data;
} TextIn[];

void main()
{
    float textSize = TextIn[0].data.x;
    float index =  TextIn[0].data.y;

    vec4 pos = gl_in[0].gl_Position;
    gl_Position =  vp * pos;
    TexCoord = vec3(0, 0, index);
    EmitVertex();

    gl_Position =  vp * (pos + (vec4(textSize, 0, 0, 0)));
    TexCoord = vec3(1.0f , 0.0f, index);
    EmitVertex();

    gl_Position =  vp * (pos +  (vec4(0, textSize, 0, 0)));
    TexCoord = vec3(0, 1, index);
    EmitVertex();

    gl_Position =  vp * (pos + (vec4(textSize, textSize, 0, 0)));
    TexCoord = vec3(1, 1, index);
    EmitVertex();
}