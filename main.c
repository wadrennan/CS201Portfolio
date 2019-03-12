#include <stdlib.h>
#include <curses.h>
#include "UI.h"
#include "game.h"
 //will return gamemode as well as board size in an array
//a[0] == gamemode, a[1] == x board size, a[2] == y board size
int main(void){
  int mainx, mainy;
  int* game;
  WINDOW* mwin;
  mwin = initscr(); //main window pointer (whole screen is a window)
  raw();
  cbreak();
  noecho(); //don't echo key presses
  curs_set(FALSE);
  mainx = getDimension('x',mwin);
  mainy = getDimension('y', mwin);
  // x and y dimensions of the main screen
  WINDOW* subwin = drawCenteredWin(mainx,mainy, 40, 15);
  game = introScreen(subwin, 40, 15); //game[0] = game type, game[1] = x of board, game[2] = y of game board

  refresh();
  wclear(subwin);
  wrefresh(subwin);
  refresh();
  delwin(subwin);
  WINDOW*** gameBoard = setUpGameBoard(mainx, mainy, game[1], game[2]);
  runGame(gameBoard, game[1], game[2], game[0]);
  return 0;
}
//maybe make this an array of various dimensions such as center etc?
