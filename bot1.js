var center = new Vector(50, 50);
var ang2 = 0;
function sign(a){
	if(a<0){
		return -1;
	}else{
		return 1;
	}
}

function main(){
	if(gameTime.cTime > 3){
		
		var a = center.sub(bot.pos);
		var ang = Math.atan2(a.y, a.x);
		var vel = bot.vel;
		var velMag = vel.mag();

		if(-sign(vel.x) == sign(Math.cos(ang))){ //Both Kinetic force and applied force are acking in the same direction
			bot.force.x = Math.cos(ang)*velMag*velMag/a.mag()-sign(Math.cos(ang));
		}else{
			bot.force.x = Math.cos(ang)*velMag*velMag/a.mag()+sign(Math.cos(ang));
		}
		if(-sign(vel.y) == sign(Math.sin(ang))){ //Both Kinetic force and applied force are acking in the same direction
			bot.force.y = Math.sin(ang)*velMag*velMag/a.mag()-sign(Math.sin(ang));
		}else{
			bot.force.y = Math.sin(ang)*velMag*velMag/a.mag()+sign(Math.sin(ang));
		}
	}else{
		bot.force.y = -30;
	}
	
	var scan = bot.scan(ang2, Math.PI/18);
	if(scan !== 0){
		bot.shoot(ang2, scan);
	}
	ang2 += Math.PI/18;
}