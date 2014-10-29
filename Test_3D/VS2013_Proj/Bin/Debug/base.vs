#define _POSITION gl_Position
attribute vec3 position; 
attribute vec3 color0; 
varying vec4 color; 
uniform mat4 MVP;
void main()                 
{                           
	gl_Position = MVP * vec4(position, 1.0); 
	vec3 color11 = position;
	color = vec4(color0,1.0);
	//color = gl_Position;
}     