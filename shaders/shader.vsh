attribute vec4 position; //position for each vertex

uniform float scale;
uniform vec2 realPosition; //this is the robots position in the world

void main(){
	gl_Position = vec4((position.x+realPosition.x)*scale-1.0, (position.y+realPosition.y)*scale-1.0, 0.0, 1.0);
}
