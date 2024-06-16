SDL = $$(sdl2-config --cflags --libs)

all:
	gcc main.c $(SDL) -Wall -o SDLTestExe
