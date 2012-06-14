v8 = -I/Users/Jonny/Dropbox/Developer/v8/include /Users/Jonny/Dropbox/Developer/v8/out/x64.release/libv8.so.1.2.3 -lpthread

jsbots: vector.o bot.o game.o vectorTemplate.o gameTemplate.o
	g++ main.cpp $(v8) bot.o vector.o game.o gameTemplate.o vectorTemplate.o -o jsbots -framework OpenGL -framework GLUT

vector.o: 
	g++ -c vector.cpp;

vectorTemplate.o: vector.h
	g++ -c vectorTemplate.cpp $(v8)

gameTemplate.o: vector.h vectorTemplate.h
	g++ -c gameTemplate.cpp $(v8)

bot.o: vector.h vectorTemplate.h
	g++ -c bot.cpp $(v8) 

game.o: vector.h bot.h gameTemplate.h vectorTemplate.h
	g++ -c game.cpp $(v8) -framework OpenGL -framework GLUT

clean:
	rm vector.o jsbots bot.o game.o gameTemplate.o vectorTemplate.o