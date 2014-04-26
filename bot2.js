console.log("Before name change");
mybot.name = "boxyoman";
console.log("After name change");

function main() {
	while(1){
		mybot.driveSpeedAngle(100, 90);
	}
}