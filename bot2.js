var angle = 0;

function main() {
	while(1){
		if(mybot.position.y > 950){
			angle = 270;
		}else if(mybot.position.y < 50){
			angle = 90;
		}
		mybot.driveSpeedAngle(50, angle);
	}
}