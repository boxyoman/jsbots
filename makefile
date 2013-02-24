iv8 = -I../v8libs/include 

av8 = ../v8libs/libv8.dylib -lpthread

jsbots: vector.o bot.o game.o vectorTemplate.o gameTemplate.o load_png.o
	g++ -m32 main.cpp $(iv8) $(av8) bot.o vector.o game.o load_png.o gameTemplate.o vectorTemplate.o -o jsbots -framework OpenGL -framework GLUT -lpng

vector.o: 
	g++ -m32 -c vector.cpp;

vectorTemplate.o: vector.h
	g++ -m32 -c vectorTemplate.cpp $(iv8)

gameTemplate.o: vector.h vectorTemplate.h
	g++ -m32 -c gameTemplate.cpp $(iv8)

bot.o: vector.h vectorTemplate.h
	g++ -m32 -c bot.cpp $(iv8) 

game.o: vector.h bot.h gameTemplate.h vectorTemplate.h game.cpp game.h load_png.h
	g++ -m32 -c game.cpp $(iv8)

load_png.o: load_png.h load_png.cpp
	g++ -arch i386 -c load_png.cpp

clean:
	rm vector.o jsbots bot.o game.o gameTemplate.o vectorTemplate.o
