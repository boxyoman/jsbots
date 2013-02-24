var ang2 = 0;


function main(){
	var scan = bot.scan(ang2, Math.PI/18);
	
			
	if(scan != 0){
		bot.shoot(ang2, scan);

		bot.force.x = 30*Math.cos(ang2);
		bot.force.x = 30*Math.sin(ang2);
		
	}else{
		if(bot.pos.y > 50){
			bot.force.y = -30;
		}else{
			bot.force.y = 30;
		}
	}
	

	ang2 += Math.PI/18;
}
