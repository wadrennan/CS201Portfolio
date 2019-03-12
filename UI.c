#include <stdlib.h>
#include <curses.h>
#include "UI.h"
#include <string.h>
/*This file should be the UI functions for connect 4 corresponding to the signatures
in the UI.h file*/

/*TO DO:
1. size WINDOWx
2. draw board w colors and stuffx
3. resize window if screen is resized
4. update according to how game is goingx
5. score window!!!!!
*/
int getDimension(char ch, WINDOW* win){
  if(ch == 'x'){
    int x =  getmaxx(win);
    return x;
  }
  else{
    int y = getmaxy(win);
    return y;
  }
}

WINDOW* drawCenteredWin(int x, int y, int width, int height){
  WINDOW* subwin;
  int centerx, centery;
  centerx = x/2;
  centery = y/2;
  subwin = newwin(height, width, centery-(height / 2), centerx - (width / 2));
  box(subwin, 0, 0);
  wrefresh(subwin);
  return subwin;
}

int* introScreen(WINDOW* win, int width, int height){
  static int game[3];
  int temp;
  int ch;
  mvwprintw(win,height/2 -1, width/4,  "Welcome to Connect 4!");
  mvwprintw(win,height/2, width/4-2,  "Press any key to continue");
  wrefresh(win);
  getchar();
  wclear(win);
  box(win, 0, 0);
  mvwprintw(win,height/2 -2, (width/4)-2,"Select a game mode!");
  mvwprintw(win,height/2 -1, (width/4)-2,"1. Single Player (not complete)");
  mvwprintw(win,height/2 , (width/4)-2,"2. Multiplayer (not complete)");
  mvwprintw(win,height/2+1, (width/4)-2,"3. AI (not complete)");
  mvwprintw(win,height/2+2, (width/4)-2,"Press h for help (not complete)");
  wrefresh(win);
  int check = 0;

  while(check == 0){
      ch = getchar();
      if(ch == 49 || ch == 50 || ch == 51 ){

        game[0] = ch -48;
        check++;

      }
      //FIXME: HELPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP
      else if(ch == 72 || ch == 104 ){
        //help window!
        mvwprintw(win, height/2+4,width/4, "Help not yet implemented");
        wrefresh(win);
      }
      else{
      mvwprintw(win, height/2+3,width/4, "Invalid Entry!");
      wrefresh(win);
      }
    }
    echo();
  wclear(win);
  box(win,0,0);
  mvwprintw(win,height/2 -1, width/4,"Enter Board Width");
  curs_set(TRUE); //display cursor\
//FIXME vet for non integer entered
  wrefresh(win);
  mvwscanw(win, height/2,width/4, "%d", &temp);
  game[1] = temp;
  mvwprintw(win,height/2 +1, width/4,"Enter Board Height");
  wrefresh(win);
  mvwscanw(win, height/2+2,width/4, "%d", &temp);
  game[2] = temp;
  wclear(win);
  box(win,0,0);
 mvwprintw(win,height/2+3, width/4,"%d , %d, %d", game[0], game[1], game[2]);
  wrefresh(win);
//  wrefresh(win);
  //wclear(win);

  return game;
}

//FIXME: Handle what happens if dimesions entered don't allow for score board
//FIXME: handle overflow!
//*************************************************FUNCTIONING**********************************************
WINDOW*** setUpGameBoard(int mainx, int mainy, int x, int y){

  int currx = (mainx/2) - ((x*3)/2);
  int curry = 0;
  int temp = currx;


  WINDOW*** wind =malloc(sizeof(WINDOW**)* y);
  for(int j = 0; j < y; j++){
  wind[j] = malloc(sizeof(WINDOW*)*x);
}
  for(int j = 0; j < y; j++){
  for( int i= 0 ; i < x; i++){
    WINDOW* name = newwin(2,3,curry,currx);
    currx = currx+3;
    box(name,0,0);
    wrefresh(name);
    wind[j][i] = name;
  }
currx = temp;
curry = curry+2;
}

  return wind;
}
//**************************************************************************************************************
int selectCol(WINDOW*** gb, int x, int y, int colorpair, int** marked){
  start_color();
  if(colorpair == 1){
  init_pair(1,COLOR_RED, COLOR_BLACK);
  init_pair(3,COLOR_BLUE, COLOR_BLACK);
}
else{
  init_pair(1,COLOR_BLUE, COLOR_BLACK);
  init_pair(3,COLOR_RED, COLOR_BLACK);
}
  init_pair(2,COLOR_WHITE, COLOR_BLACK);

  curs_set(FALSE);
  noecho();
  int currx = 0;
  int curry = y-1;
  int i = curry-1;
  if(marked[curry][currx] != 0){
    while(marked[curry][currx] != 0){
    curry--;
    if(curry == -1){
      curry = y-1;
      currx++;
      }
    }
  }// y is reversed!!!
  wbkgd(gb[curry][currx], COLOR_PAIR(1));
  wrefresh(gb[curry][currx]);
    keypad(gb[curry][currx],TRUE);
  int ch = wgetch(gb[curry][currx]);

  refresh();
  while(ch != 's' ){ // q is quit s is select
      keypad(gb[curry][currx],FALSE);
    if(ch == KEY_LEFT  && currx-1 != -1){
      if(marked[curry][currx-1] ==1 ){
//        wbkgd(gb[curry][currx], COLOR_PAIR(3));
    //  printw("left");
    //  refresh();
      }
      else{
        wbkgd(gb[curry][currx], COLOR_PAIR(2));

      wrefresh(gb[curry][currx]);
      currx--;
      wbkgd(gb[curry][currx], COLOR_PAIR(1));
      wrefresh(gb[curry][currx]);
      }
    }
    else if(ch == KEY_RIGHT && currx+1 != x){
      if(marked[curry][currx+1] ==1 ){
      //  wbkgd(gb[curry][currx], COLOR_PAIR(3));
    //  printw("right");
    //  refresh();
      }
      else{
        wbkgd(gb[curry][currx], COLOR_PAIR(2));

      wrefresh(gb[curry][currx]);
      currx++;
      wbkgd(gb[curry][currx], COLOR_PAIR(1));
      wrefresh(gb[curry][currx]);
      }
    }
    else if(ch == KEY_DOWN  && curry+1 != y){
      if(marked[curry+1][currx] ==1 ){
    //    wbkgd(gb[curry][currx], COLOR_PAIR(3));

    //  printw("down");
    //  refresh();
      }
      else{
      wbkgd(gb[curry][currx], COLOR_PAIR(2));
      wrefresh(gb[curry][currx]);
      curry++;
      wbkgd(gb[curry][currx], COLOR_PAIR(1));
      wrefresh(gb[curry][currx]);
    }
  }//*****************************************************************************************FIXME UP AND DOWN MEMORY LEAK TOP 2 ROWS???
    else if(ch == KEY_UP  && curry-1 != -1){
      if(marked[curry-1][currx] ==1 ){
        //wbkgd(gb[curry][currx], COLOR_PAIR(3));
        //printw("up");
        //refresh();
      }
      else{
      wbkgd(gb[curry][currx], COLOR_PAIR(2));
      wrefresh(gb[curry][currx]);
      curry--;
      wbkgd(gb[curry][currx], COLOR_PAIR(1));
      wrefresh(gb[curry][currx]);
    }
  }
      keypad(gb[curry][currx],TRUE);
    ch = wgetch(gb[curry][currx]);
}
    wbkgd(gb[curry][currx], COLOR_PAIR(2));
    wrefresh(gb[curry][currx]);
  return currx;
}

void moveSpot(WINDOW*** gb, int x, int num, int y, int colorpair){
  if(colorpair == 1){
    init_pair(1,COLOR_RED, COLOR_BLACK);
  }
  else{
    init_pair(1,COLOR_BLUE, COLOR_BLACK);
  }
 wbkgd(gb[y-1-num][x], COLOR_PAIR(1));
 wrefresh(gb[y-1-num][x]);
return;
}