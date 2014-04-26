mybot.name = "Jonny";

var angle = 0;

function main() {
	console.log(shoot(0, 400));
	while(1){
		if(mybot.position.x > 950){
			angle = 180;
		}else if(mybot.position.x < 50){
			angle = 0;
		}
		mybot.driveSpeedAngle(50, angle);
	}
}
function test() {
	console.log("test function");
}