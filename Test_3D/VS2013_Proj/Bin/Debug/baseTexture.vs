#define _POSITION gl_Position
attribute vec3 position; 
attribute vec2 color0; 
varying vec2 uv;
uniform mat4 MVP;
void main()                 
{                           
	gl_Position = MVP * vec4(position, 1.0); 
	uv =  color0;
	
}     