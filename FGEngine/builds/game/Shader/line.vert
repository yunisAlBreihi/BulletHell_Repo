#version 440 core
layout (location = 0) in vec4 Points;
layout (location = 1) in vec4 ColorAndSize;
out LineInfo{
   vec2 endPoint;
   vec4 colorAndSize;
} LineOut;

void main()
{
	gl_Position = vec4(Points.xy, 0.0, 1.0);	
    LineOut.endPoint = Points.zw;
    LineOut.colorAndSize = ColorAndSize;
}