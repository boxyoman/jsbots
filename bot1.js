var center = new Vector(400, 300);

function main(){
	/*if(gameTime.cTime > 6){
		bot.force.y = 0;
		/*var a = center.sub(bot.pos);
		var ang = Math.atan2(a.y, a.x);
		
		bot.force.x = Math.cos(ang)*100;
		bot.force.y = Math.sin(ang)*100;
	}else{
		bot.force.y = -30;
	}*/
	bot.shoot(3*Math.PI/2, 80);
	
}