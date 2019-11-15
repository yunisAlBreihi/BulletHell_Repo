#version 440 core
layout (location = 0) in vec4 rect;
out RectInfo{
   vec2 data;
} RectOut;

void main()
{
	gl_Position = vec4(rect.xy, 0.0, 1.0);	
    RectOut.data = rect.zw;
}