var center = new Vector(50, 50);
var ang2 = 0;
function main(){
	if(gameTime.cTime > 6){
		
		var a = center.sub(bot.pos);
		var ang = Math.atan2(a.y, a.x);
		
		bot.force.x = Math.cos(ang)*100;
		bot.force.y = Math.sin(ang)*100;
	}else{
		bot.force.y = -30;
	}
	bot.shoot(3*Math.PI/2, 80);
	/*
	var scan = bot.scan(ang2, Math.PI/18);
	if(scan !== 0){
		bot.shoot(ang2, scan);
	}
	ang2 += Math.PI/18;*/
}