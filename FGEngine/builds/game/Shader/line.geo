#version 440 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;
uniform mat4 vp;
out vec2 TexCoord;
out vec3 Color;

in LineInfo{
   vec2 endPoint;
   vec4 colorAndSize;
} LineIn[];

vec2 rotatePoint(vec2 point, float angle)
{

        vec2 p = vec2(0, 0);
        float s = sin(angle);
        float c = cos(angle);

        // translate point back to origin:
        p.x -= point.x;
        p.y -= point.y;

        // rotate point
        float xnew = p.x * c - p.y * s;
        float ynew = p.x * s + p.y * c;

        // translate point back:
        p.x = xnew;
        p.y = ynew;
        return p;
}


void main()
{
    float lineSize = LineIn[0].colorAndSize.w;
    vec2 lineDest = LineIn[0].endPoint - gl_in[0].gl_Position.xy;
    float lineLength = length(lineDest);

    
    float angle = atan(lineDest.x, lineDest.y);
    
    //left top rendering
    gl_Position = vp * (gl_in[0].gl_Position);
    TexCoord = vec2(0, 0);
    Color = LineIn[0].colorAndSize.xyz;
    EmitVertex();

    gl_Position =  vp *(gl_in[0].gl_Position + (vec4(rotatePoint(vec2(lineLength, 0), angle).xy, 0, 0)));
    TexCoord = vec2(1, 0);
    Color = LineIn[0].colorAndSize.xyz;
    EmitVertex();

    gl_Position = vp *(gl_in[0].gl_Position + (vec4(rotatePoint(vec2(0, lineSize).xy, angle), 0, 0)));// vec4(0, lineSize, 0, 0)); //(vec4(rotatePoint(vec2(0, lineSize).xy, angle), 0, 0)));
    TexCoord = vec2(0, 1);
    Color = LineIn[0].colorAndSize.xyz;
    EmitVertex();

    gl_Position = vp *(gl_in[0].gl_Position +  (vec4(rotatePoint(vec2(lineLength, lineSize), angle).xy, 0, 0)));
    TexCoord = vec2(1, 1);
    Color = LineIn[0].colorAndSize.xyz;
    EmitVertex();
}