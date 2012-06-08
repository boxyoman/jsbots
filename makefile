v8 = -I/Users/Jonny/Dropbox/Developer/v8/include /Users/Jonny/Dropbox/Developer/v8/out/x64.release/libv8.so.1.2.3 -lpthread

jsbots: vector.o bot.o game.o
	g++ main.cpp $(v8) bot.o vector.o game.o gameTemplate.o -o jsbots -framework OpenGL -framework GLUT

game.o: vector.o bot.o gameTemplate.o
	g++ -c game.cpp $(v8) vector.o bot.o gameTemplate.o -framework OpenGL -framework GLUT

bot.o: vector.o
	g++ -c bot.cpp $(v8) vector.o

gameTemplate.o: vector.o
	g++ -c gameTemplate.cpp $(v8) vector.o

vector.o: 
	g++ -c vector.cpp;

clean:
	rm vector.o jsbots bot.o game.o gameTemplate.o