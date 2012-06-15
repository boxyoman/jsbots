//bot.pos.x = 300;
//main is the loop function

function main(){
	if(bot.pos.x > 600 && bot.pos.y > 400){
		bot.force.x = -40;
		bot.force.y = -100;
	}else if(bot.pos.x > 600 && bot.pos.y <= 150){
		bot.force.x = -100;
		bot.force.y = 50;
	}else if(bot.pos.x < 200 && bot.pos.y <= 150){
		bot.force.x = 40;
		bot.force.y = 100;
	}else if(bot.pos.x < 200 && bot.pos.y > 400){
		bot.force.x = 100;
		bot.force.y = -40;
	}
	/*var scan = bot.scan(3*Math.PI/4, 2*Math.PI/8);
	if(scan != 0){
		//log(scan);
	}*/
}