//bot.pos.x = 300;
//main is the loop function
var ang = 0;
function main(){
	
	bot.force.x = 50;
	
	var scan = bot.scan(ang, Math.PI/8);
	if(scan != 0){
		bot.shoot(ang, scan);
	}
	//ang += Math.PI/8;
}