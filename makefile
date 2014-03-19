CC = gcc
OBJ = vector.o

jsbots: main.m $(OBJ)
	$(CC) $< -o $@ $(OBJ) -framework OpenGL -framework JavaScriptCore -framework Foundation
%.o: $.m %.h
	$(CC) -c -o $@ $<

clean:
	rm jsbots *o
