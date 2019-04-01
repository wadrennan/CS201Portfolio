main: main.c UI.c game.c stack.c
	gcc  main.c UI.c game.c stack.c -lncurses -std=c11 -Wall -o connectfour
