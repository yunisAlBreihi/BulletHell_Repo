#version 440 core
layout (location = 0) in vec4 rect;
layout (location = 1) in vec4 border;
layout (location = 2) in vec4 fill;
out RectInfo{
   vec2 data;
} RectOut;

out vec4 GEOFill;
out vec4 GEOBorder;

void main()
{
	gl_Position = vec4(rect.xy, 0.0, 1.0);	
    RectOut.data = rect.zw;
    GEOFill = fill;
    GEOBorder = border;
}