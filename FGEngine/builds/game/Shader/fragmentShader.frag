#version 440 core
in vec3 TexCoord;
out vec4 frag_color;

uniform sampler2DArray textureArray; 

void main()
{
	frag_color = texture(textureArray, TexCoord);
}
