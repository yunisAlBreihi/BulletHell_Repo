#version 440 core
layout (location = 0) in vec4 aPos;

out TextInfo{
   vec2 data;
} TextOut;

void main()
{
	gl_Position = vec4(aPos.xy, 0.0, 1.0);	
   TextOut.data = aPos.zw;
}