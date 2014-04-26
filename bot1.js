mybot.name = "Jonny";

var angle = 0;

function main() {
	while(1){
		if(mybot.position.x > 950){
			angle = 180;
		}else if(mybot.position.x < 50){
			angle = 0;
		}
		drive(50, angle);
		shoot(0,400);
	}
}
function test() {
	console.log("test function");
}