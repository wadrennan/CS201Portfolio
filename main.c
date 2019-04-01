#include <stdlib.h>
#include <curses.h>
#include "UI.h"
#include "game.h"
 //will return gamemode as well as board size in an array
//a[0] == gamemode, a[1] == x board size, a[2] == y board size
int main(void){
  int mainx, mainy;
  int p1count =0;
  int p2count =0;
  int winner;
  int* game;
  WINDOW* mwin;
  char gamecheck = 'y';
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
  int gamecount = 0;
  WINDOW*** gameBoard ;

  while(gamecheck == 'y'){
    mvprintw(0,0,"Match count: %d",gamecount);
    mvprintw(1,0,"P1 Wins: %d", p1count);
    mvprintw(2,0,"P2 Wins: %d", p2count);
    refresh();

  gameBoard = setUpGameBoard(mainx, mainy, game[1], game[2]);
  refresh();
//getch();

  winner = runGame(gameBoard, game[1], game[2], game[0], mainx, mainy);
  gamecount++;
  if(winner == 1){
    p1count++;
  }
  else if(winner ==2){
    p2count++;
  }

    clear();
    refresh();
    //free everything
if(game[1] < 31 && game[2] < 21){ // checked

  for(int i = 0; i < game[1]; i++){
    for(int j = 0; j < game[2]; j++){

      wclear(gameBoard[j][i]);
      wrefresh(gameBoard[j][i]);
      delwin(gameBoard[j][i]);
    }
  }
}
else if(game[1] < 31){ //checked

  for(int i = 0; i < game[1]; i++){
    for(int j = 0; j < 20; j++){

      wclear(gameBoard[j][i]);
      wrefresh(gameBoard[j][i]);
      delwin(gameBoard[j][i]);
    }
  }
}
else if(game[2] < 21){ //checked
  for(int i = 0; i < 30; i++){
    for(int j = 0; j < game[2]; j++){

      wclear(gameBoard[j][i]);
      wrefresh(gameBoard[j][i]);
      delwin(gameBoard[j][i]);
    }
  }
}
else{ //checked

  for(int i = 0; i < 30; i++){
    for(int j = 0; j < 20; j++){

      wclear(gameBoard[j][i]);
      wrefresh(gameBoard[j][i]);
      delwin(gameBoard[j][i]);
    }
  }
}
  gamecheck = playAgain(mainx, mainy);
}



  delwin(stdscr);
  endwin();
  return 0;
}

//maybe make this an array of various dimensions such as center etc?
