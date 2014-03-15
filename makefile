bots: 
	g++ main.m -o jsbots -framework OpenGL -framework JavaScriptCore -framework Foundation

clean:
	rm jsbots
