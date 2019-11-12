#version 440 core

#define TEXTURE_ARRAY_MAX_SIZE 16

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;
uniform mat4 vp;
uniform vec4 tilemapDataArray[TEXTURE_ARRAY_MAX_SIZE];
out vec3 TexCoord;


mat4 rotationZ( in float angle ) {
	return mat4(	cos(angle),		-sin(angle),	0,	0,
			 		sin(angle),		cos(angle),		0,	0,
							0,				0,		1,	0,
							0,				0,		0,	1);
}

in SpriteInfo{
   vec4 data;
} SpriteIn[];

void main()
{

    float spriteWidth = SpriteIn[0].data.x;
    float spriteHeight = SpriteIn[0].data.y;

    highp int index = int(SpriteIn[0].data.w) >> 16 ;
    highp int textureIndex = int(SpriteIn[0].data.w) & 0xffff;

    vec4 tileMapData = tilemapDataArray[textureIndex];

    float theta = SpriteIn[0].data.z;
    mat4 rotation = rotationZ(theta);

    highp int nWidth = int(tileMapData.z);
    float yIndex = index / nWidth;
    float xIndex = index % nWidth;

    gl_Position = vp *(gl_in[0].gl_Position + (vec4(-spriteWidth, -spriteHeight, 0, 0)) * rotation);
    TexCoord = vec3((xIndex+1) * tileMapData.x, tileMapData.y * (yIndex+1), textureIndex);
    EmitVertex();

    gl_Position =  vp *(gl_in[0].gl_Position + (vec4(spriteWidth, -spriteHeight, 0, 0)) * rotation); 
    TexCoord = vec3(xIndex * tileMapData.x, tileMapData.y * (yIndex+1), textureIndex);
    EmitVertex();

    gl_Position = vp *(gl_in[0].gl_Position + (vec4(-spriteWidth, spriteHeight, 0, 0))* rotation);
    TexCoord = vec3((xIndex+1) * tileMapData.x, tileMapData.y * yIndex, textureIndex);
    EmitVertex();

    gl_Position = vp *(gl_in[0].gl_Position +  (vec4(spriteWidth, spriteHeight, 0, 0))* rotation);
    TexCoord = vec3(xIndex * tileMapData.x, tileMapData.y * yIndex, textureIndex);
    EmitVertex();
}