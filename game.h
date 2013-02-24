#ifndef _GAME_H_
#define _GAME_H_


using namespace v8;
using namespace std;

enum{
	gl_ship,
	gl_bullet,
	gl_scanner,
	gl_explode,
  gl_num
};

typedef struct{
	vector<double> pos;
	vector<double> dest;
	double explodeTime;
	int deathCheck;
	int ison;
}bullet;

class game: public gamePrototype{
	public:
		game(int argc, char* argv[]);
		void init();
		void start();
		int numBots;
		jsbot **bots;	
		bullet bullets[10];
		
		//Textures
		GLuint tex[gl_num];
		
		
		double scan(double ang, double width, void* bot);
		int shoot(double ang, double distance, void* bot);
	
	
	private:
		static void loop();
		static void draw();
		static void update();
		static void changeSize(int, int);
		static void idle();
};

#endif