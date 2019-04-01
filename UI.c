#include <stdlib.h>

#include <ncurses.h>

#include "UI.h"

#include <string.h>

/*This file should be the UI functions for connect 4 corresponding to the signatures

in the UI.h file*/


int getDimension(char ch, WINDOW* win){

  if(ch == 'x'){

    int x =  getmaxx(win);

  //  printw("%d ", x);

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

//  box(subwin, 0, 0);

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
  //box(win, 0, 0);
  mvwprintw(win,height/2 -2, (width/4)-2,"Select a game mode!");
  mvwprintw(win,height/2 -1, (width/4)-2,"1. Single Player");
  mvwprintw(win,height/2 , (width/4)-2,"2. Multiplayer");

  wrefresh(win);
  int check = 0;
  while(check == 0){
      ch = getchar();
      if(ch == 49 || ch == 50 ){
        game[0] = ch -48;
        check++;
      }

      else{
      mvwprintw(win, height/2+3,width/4, "Invalid Entry!");
      wrefresh(win);
      }
    }
    echo();
  wclear(win);
  //box(win,0,0);
  mvwprintw(win,height/2 -4, width/4,"Enter Board Width (min 4) ");
  mvwprintw(win,height/2 -3, width/4,"(Warning: takes ASCII ");
  mvwprintw(win,height/2 -2, width/4,"of non-integer input) ");
  curs_set(TRUE); //display cursor
  wrefresh(win);
while(1){
  mvwscanw(win, height/2-1,width/4, "%d", &temp);
  if(temp < 4){
    mvwprintw(win,height/2 , width/4,"Please enter a value >=4");
  }
  else{
    break;
  }
}
  game[1] = temp;

  mvwprintw(win,height/2 +1, width/4,"Enter Board Height (min 4)");
  while(1){
    mvwscanw(win, height/2+2,width/4, "%d", &temp);
    if(temp <4){
      mvwprintw(win,height/2+3 , width/4,"Please enter a value >=4");
    }
    else{
      break;
    }
  }
  game[2] = temp;
  wclear(win);
 mvwprintw(win,height/2+3, width/4,"%d , %d, %d", game[0], game[1], game[2]);
  wrefresh(win);
  return game;
}

void extendScreen(WINDOW*** gb, int** marked, int x, int y, int type, int extensionNumy, int extensionNumx){
  start_color();
  init_pair(1,COLOR_RED, COLOR_BLACK);
  init_pair(2,COLOR_WHITE, COLOR_BLACK);
  init_pair(3,COLOR_BLUE, COLOR_BLACK);

  refresh();
  int extendy = 0;
  int extendx = 0;
  if( y > 21){
    extendy = 20;
  }
  else{
    extendy = y;
  }
  if(x > 31){
    extendx = 30;
  }
  else{
    extendx = x;
  }
  if(type ==1){//recolor appropriate portions of board
    //y extension
        int temp = y-(20*extensionNumy);
        if(20 - temp < 0){
          //full extension;
          for(int i = 0; i < extendx; i++){
            for(int j = 0; j < 20; j++){
              if(marked[y-1-(20*extensionNumy)-j][(30*extensionNumx)+i] ==1 ){
                wbkgd(gb[extendy - j - 1][i], COLOR_PAIR(1));
                wrefresh(gb[extendy-j-1][i]);
                refresh();
              }
              else if(marked[y-1-(20*extensionNumy)-j][(30*extensionNumx)+i] ==2 ){
                wbkgd(gb[20 - j - 1][i], COLOR_PAIR(3));
                wrefresh(gb[20-j-1][i]);
                refresh();
              }
              else{
                wbkgd(gb[20 - j - 1][i], COLOR_PAIR(2));
                wrefresh(gb[20-j-1][i]);
                refresh();
              }
            }
          }
        }
        else{
          //partial
          for(int i = 0; i < extendx; i++){//recolor appropriate portions of board
            for(int j = 0; j < 20; j++){

              if(marked[y-20+j][(30*extensionNumx)+i] ==1 ){
                wbkgd(gb[j][i], COLOR_PAIR(1));
                wrefresh(gb[j][i]);
                refresh();
              }
              else if(marked[y-20+j][(30*extensionNumx)+i] ==2 ){
                wbkgd(gb[j][i], COLOR_PAIR(3));
                wrefresh(gb[j][i]);
              }
              else{
                wbkgd(gb[j][i], COLOR_PAIR(2));
                wrefresh(gb[j][i]);
              }
            }

          }
        }

    }



  else{
    //x extension

    int temp = x-(30*extensionNumx); // 30 is default width per panel for boards greater than 30 width

      if( 30 - temp < 0){//fully new section of board
          for(int i = 0; i < 30; i++){
            for(int j = 0; j < extendy; j++){
              if(marked[y-(20*extensionNumy)-j-1][(30*extensionNumx)+i] ==1 ){
                wbkgd(gb[extendy - j - 1][i], COLOR_PAIR(1));
                wrefresh(gb[extendy-j-1][i]);
                refresh();
              }
              else if(marked[y-(20*extensionNumy)-j-1][(30*extensionNumx)+i] ==2 ){
                wbkgd(gb[extendy-j-1][i], COLOR_PAIR(3));
                wrefresh(gb[extendy-j-1][i]);
              }
              else{
                wbkgd(gb[extendy-j-1][i], COLOR_PAIR(2));
                wrefresh(gb[extendy-j-1][i]);
              }
            }
          }
      }
      else{
        //partial extension

        for(int i = 0; i < 30; i++){//recolor appropriate portions of board
          for(int j = 0; j < extendy; j++){
            if(marked[y-(20*extensionNumy)-j-1][x-30+i] ==1 ){
              wbkgd(gb[extendy - j - 1][i], COLOR_PAIR(1));
              wrefresh(gb[extendy-j-1][i]);
              refresh();
            }
            else if(marked[y-j-(20*extensionNumy)-1][x-30+i] ==2 ){
              wbkgd(gb[extendy-j-1][i], COLOR_PAIR(3));
              wrefresh(gb[extendy-j-1][i]);
            }
            else{
              wbkgd(gb[extendy-j-1][i], COLOR_PAIR(2));
              wrefresh(gb[extendy-j-1][i]);
            }
          }
        }
      }
    }
  return;
}



WINDOW*** setUpGameBoard(int mainx, int mainy, int x, int y){
  int currx;
  //centering game board
  if(x > 30){
    currx = (mainx/2) - ((30*3)/2);
  }
  else{
    currx = (mainx/2) - ((x*3)/2);
  }

  int curry = 0;
  int temp = currx;

if(x > 31){
  x = 30;
}
if(y > 21){
  y = 20;
}
//allocate gameboard
  WINDOW*** wind =malloc(sizeof(WINDOW**)* y);
  for(int j = 0; j < y; j++){
  wind[j] = malloc(sizeof(WINDOW*)*x);
}
//each spot is its own window
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



int selectCol(WINDOW*** gb, int x, int y, int colorpair, int** marked, WINDOW* coords){

  /* controls moving pieces, doesn't allow for collision of pieces, use arrow keys*/

  start_color();
  init_pair(1,COLOR_RED, COLOR_BLACK);
  init_pair(2,COLOR_WHITE, COLOR_BLACK);
  init_pair(3,COLOR_BLUE, COLOR_BLACK);
  curs_set(FALSE);
  noecho();
int curry = 0; //y that you're at on the board
int origcurry = 0; // starting y
  int currx = 0; // x that you're at on the board
  int extendNumx =0; //number of extensions
  int extendNumy = 0; //number of extensions
  if(y < 21){
   curry = y-1;
  origcurry = y-1;
  }
  else{
    curry= 19;
    origcurry = 19;
  }

  int realy = y-1;
  int realx = 0;
  //coordinate window so you can follow through huge boards
  wclear(coords);
  mvwprintw(coords,0,0, "X : %d",realx);
  mvwprintw(coords,1,0, "Y : %d",y - realy);
  mvwprintw(coords,2,0, "Press s to select");
  mvwprintw(coords,3,0, "Press q to quit between turns");
  wrefresh(coords);
  if(marked[realy][currx] != 0){
    while(marked[realy][currx] != 0){
    curry--;
    realy--;
    if(curry == -1){
      curry = origcurry;
      realy = y-1;
      currx++;
      realx++;
      }
    }
  }
  //color assignment
  if(colorpair == 1){
  wbkgd(gb[curry][currx], COLOR_PAIR(1));
  }
  else{
    wbkgd(gb[curry][currx], COLOR_PAIR(3));
  }
  wrefresh(gb[curry][currx]);
  keypad(gb[curry][currx],TRUE);
  int ch = wgetch(gb[curry][currx]);
  refresh();
  while(ch != 's' ){ // q is quit s is select
      keypad(gb[curry][currx],FALSE);
    //Following code moves pieces around with arrows and extends where appropriate
    if(ch == KEY_LEFT  && realx-1 != -1){

      if(marked[realy][currx-1] ==1 || marked[realy][currx-1] ==2 ){

      }
    else if(realx -1 != -1){
       if(x > 30 && currx-1 ==-1  && marked[realy][realx-1] == 0 ){
          extendNumx--;
        extendScreen(gb,marked,x,y,2,extendNumy,extendNumx);
            wbkgd(gb[curry][currx],COLOR_PAIR(2));
            wrefresh(gb[curry][currx]);
        if(x-30 > 30){
          currx = 29;
        }
        else{
          currx = (x-30);
        }
        realx--;
        if(colorpair == 1){
        wbkgd(gb[curry][currx], COLOR_PAIR(1));
        }
        else{
          wbkgd(gb[curry][currx], COLOR_PAIR(3));
        }
        wrefresh(gb[curry][currx]);
        wclear(coords);
        mvwprintw(coords,0,0, "X : %d",realx);
        mvwprintw(coords,1,0, "Y : %d",y - realy-1);
        mvwprintw(coords,2,0, "Press s to select");
          mvwprintw(coords,3,0, "Press q to quit between turns");
        wrefresh(coords);
      }
      else{
        wbkgd(gb[curry][currx], COLOR_PAIR(2));
      wrefresh(gb[curry][currx]);
      currx--;
      realx--;
      wclear(coords);
      mvwprintw(coords,0,0, "X : %d",realx);
      mvwprintw(coords,1,0, "Y : %d",y - realy-1);
      mvwprintw(coords,2,0, "Press s to select");
        mvwprintw(coords,3,0, "Press q to quit between turns");
      wrefresh(coords);
      if(colorpair == 1){
      wbkgd(gb[curry][currx], COLOR_PAIR(1));
      }
      else{
        wbkgd(gb[curry][currx], COLOR_PAIR(3));
      }
      wrefresh(gb[curry][currx]);
      }
    }
    }
    else if(ch == KEY_RIGHT && realx+1 != x){
      if(marked[realy][currx+1] ==1 || marked[realy][currx+1] ==2){
      }
      else if(x > 30 && currx+1 ==30){
          extendNumx++;
        extendScreen(gb,marked,x,y,2,extendNumy, extendNumx);

            wbkgd(gb[curry][currx],COLOR_PAIR(2));
            wrefresh(gb[curry][currx]);
        if(x-30 > 30){
        currx = 0;
        }
        else{
          currx = 30 - (x-30);
        }
        if(colorpair == 1){
        wbkgd(gb[curry][currx], COLOR_PAIR(1));
        }
        else{
          wbkgd(gb[curry][currx], COLOR_PAIR(3));
        }
        wrefresh(gb[curry][currx]);

        realx++;

        wclear(coords);
        mvwprintw(coords,0,0, "X : %d",realx);
        mvwprintw(coords,1,0, "Y : %d",y - realy-1);
        mvwprintw(coords,2,0, "Press s to select");
          mvwprintw(coords,3,0, "Press q to quit between turns");
        wrefresh(coords);
      }
      else{
        wbkgd(gb[curry][currx], COLOR_PAIR(2));
      wrefresh(gb[curry][currx]);
      currx++;
      realx++;
      wclear(coords);
      mvwprintw(coords,0,0, "X : %d",realx);
      mvwprintw(coords,1,0, "Y : %d",y - realy-1);
      mvwprintw(coords,2,0, "Press s to select");
        mvwprintw(coords,3,0, "Press q to quit between turns");
      wrefresh(coords);
      if(colorpair == 1){
      wbkgd(gb[curry][currx], COLOR_PAIR(1));
      }
      else{
        wbkgd(gb[curry][currx], COLOR_PAIR(3));
      }
      wrefresh(gb[curry][currx]);
      }
    }

    else if(ch == KEY_DOWN  && realy+1 != y){

      if(marked[realy+1][currx] ==1 || marked[realy+1][currx] ==2){
      }
      else if(y>20 && curry+1 ==20 ){
        extendNumy--;
        extendScreen(gb,marked,x,y,1,extendNumy,extendNumx);
        realy--;
        if(y-20> 20){
          curry = 0;
        }
        else{
          curry =(y-19);
        }
      }
      else{
      wbkgd(gb[curry][currx], COLOR_PAIR(2));
      wrefresh(gb[curry][currx]);
      curry++;
      realy++;
      wclear(coords);
      mvwprintw(coords,0,0, "X : %d",realx);
      mvwprintw(coords,1,0, "Y : %d",y - realy -1);
      mvwprintw(coords,2,0, "Press s to select");
        mvwprintw(coords,3,0, "Press q to quit between turns");
      wrefresh(coords);
      if(colorpair == 1){
      wbkgd(gb[curry][currx], COLOR_PAIR(1));
      }
      else{
        wbkgd(gb[curry][currx], COLOR_PAIR(3));
      }
      wrefresh(gb[curry][currx]);
    }
  }

    else if(ch == KEY_UP  && realy-1 != -1){
      if(marked[realy-1][currx] ==1 || marked[realy-1][currx] ==2 ){

      }
      else if(y > 20 && curry-1 == -1){
        extendNumy++;
        realy++;
        extendScreen(gb,marked,x,y,1,extendNumy,extendNumx);

        if(y-20 > 20){
          curry = 19;
        }
        else{
          curry = (y-20);
        }
      }
      else{
      wbkgd(gb[curry][currx], COLOR_PAIR(2));
      wrefresh(gb[curry][currx]);
      curry--;
      realy--;
      wclear(coords);
      mvwprintw(coords,0,0, "X : %d",realx);
      mvwprintw(coords,1,0, "Y : %d",y - realy-1);
      mvwprintw(coords,2,0, "Press s to select");
        mvwprintw(coords,3,0, "Press q to quit between turns");
      wrefresh(coords);
      if(colorpair == 1){
      wbkgd(gb[curry][currx], COLOR_PAIR(1));
      }
      else{
        wbkgd(gb[curry][currx], COLOR_PAIR(3));
      }
      wrefresh(gb[curry][currx]);
    }
  }
      keypad(gb[curry][currx],TRUE);
    ch = wgetch(gb[curry][currx]);
}
//resets the move back to first panel in case there was a board bigger than 30X20
  wbkgd(gb[curry][currx], COLOR_PAIR(2));
  wrefresh(gb[curry][currx]);
  if(x > 30){
    for(int i = 0; i < 30; i++){
      for(int  j = 0 ; j < origcurry; j++){
        if(marked[y-j-1][i] ==1 ){
          wbkgd(gb[origcurry -j][i], COLOR_PAIR(1));
          wrefresh(gb[origcurry-j][i]);
        }
        else if(marked[y-j-1][i] ==2 ){
          wbkgd(gb[origcurry-j][i], COLOR_PAIR(3));
          wrefresh(gb[origcurry-j][i]);
        }
        else{
          wbkgd(gb[origcurry-j][i], COLOR_PAIR(2));
          wrefresh(gb[origcurry-j][i]);
        }
      }
    }
  }
  //returns column number
  return realx;
}



void moveSpot(WINDOW*** gb, int x, int num, int y, int colorpair){

  if(y > 20){
    y = 20;
  }
  //Moves piece in selected column down to bottom-most unoccupied spot in column
  if(colorpair ==1 && y-1-num < 20){
    wbkgd(gb[y-1-num][x], COLOR_PAIR(1));
    wrefresh(gb[y-1-num][x]);
   return;
  }
 else if(y-1-num < 20){
   wbkgd(gb[y-1-num][x], COLOR_PAIR(3));
   wrefresh(gb[y-1-num][x]);
  return;
 }

}



char playAgain(int x, int y){
  WINDOW* win = drawCenteredWin(x, y, 40,15);
  mvwprintw(win, 15/2, 40/4, "Play Again ?");
  wrefresh(win);
  char answer;
  while(answer!='n' && answer!= 'y'){
  answer = getchar();
  }
  wclear(win);
  wrefresh(win);
  delwin(win);
  return answer;
}
