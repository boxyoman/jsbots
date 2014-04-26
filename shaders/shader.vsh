attribute vec4 position;

uniform float scale;
uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

void main(){
	gl_Position = vec4(position.x*scale, position.y*scale, 0.0, 1.0);
}
