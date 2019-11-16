#version 440 core
uniform float border_width;
uniform float aspect;
in vec2 TexCoord;
out vec4 frag_color;

void main() {
   float maxX = 1.0 - 0.01;
   float minX = 0.01;
   float maxY = maxX / 1.0;
   float minY = minX / 1.0;

   if (TexCoord.x < maxX && TexCoord.x > minX 
   &&
       TexCoord.y < maxY && TexCoord.y > minY) {
     frag_color = vec4(0.0f, 0.0f, 0.0f, 0.0f);
   } else {
     frag_color = vec4(0.0f, 1.0f, 0.0f, 1.0f);
   }
}