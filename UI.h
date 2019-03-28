#ifndef _UI_h
#define _UI_h
int getDimension(char ch, WINDOW* win); // gets selected dimension of screen

WINDOW* drawCenteredWin(int x, int y, int width, int height); //draws a window of a certain width and length at a specific (x,y) on screen

int* introScreen(WINDOW* win, int width, int height); //will return gamemode as well as board size in an array, handles screen arrangement

WINDOW*** setUpGameBoard(int mainx, int mainy, int x, int y); /*makes the game board for the connect 4 games; Returns a dynamically allocated array of WINDOW* that represent each spot on board*/

int selectCol(WINDOW*** gb, int x, int y, int colorpair, int** marked);
 // allows user to select spot on board; colorpair denotes which player in 2 player mode
void moveSpot(WINDOW*** gb, int x, int num, int y, int colorpair);
 // moves marked space on board down column to first unmarked space
 char playAgain(int x, int y);
#endif
