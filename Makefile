all: main.c
	gcc -std=c89 -pedantic -Wall -Wextra -lSDL2 -lSDL2_ttf main.c
