CC = clang
CFLAGS = -Wall -fobjc-arc
OBJ = vector.o jsbot.o game.o console.o myApp.o openGL.o
FRAMEWORKS = -framework OpenGL -framework JavaScriptCore -framework Foundation -framework Cocoa -framework AppKit

jsbots: main.m $(OBJ)
	$(CC) $< -o $@ $(OBJ) $(FRAMEWORKS) $(CFLAGS)

%.o: %.m %.h
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm jsbots *o
