//bot.pos.x = 300;
//main is the loop function
var ang = 0;
bot.force.x = 10;
bot.force.y = 10;
function main(){
	if(bot.pos.x<=15){
		bot.force.x = 10;
	}else if(bot.pos.x > 85){
		bot.force.x = -10;
	}
	if(gameTime.cTime > 4){
		bot.force.y = 0;
	}
	
	var scan = bot.scan(ang, Math.PI/18);
	if(scan !== 0){
		bot.shoot(ang, scan);
	}
	ang += Math.PI/18;
}