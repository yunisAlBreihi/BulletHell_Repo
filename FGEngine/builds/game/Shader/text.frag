#version 440 core
in vec3 TexCoord;
out vec4 frag_color;

uniform sampler2DArray texArray; 

void main()
{
	float t = texture(texArray, TexCoord).x;
	float a = texture(texArray, TexCoord).a;

	if(t > 0.0f)
	{
		frag_color = vec4(1.0f, 1.0f, 1.0, a);
	}
	else
	{
		frag_color = vec4(0.0f, 0.0f, 0.0f, 0);
	}
}
