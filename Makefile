all:
	clang++ -I source -g source/main.cpp -o build/FG -lSDL2 -lGL -lGLEW

debug:
	clang++ -D DEBUG=1 -I source -g source/main.cpp -o build/FG -lSDL2 -lGL -lGLEW

# yes, it works.