#include "Screen.h"
#include <pthread.h>
#include <ncurses.h>
#include <iostream>
#include <string>


Screen::Screen(){

  initscr();
  noecho();
  curs_set(0);
  start_color();
  init_pair(1,COLOR_RED, COLOR_BLACK);
  init_pair(2,COLOR_GREEN, COLOR_BLACK);
  init_pair(4,COLOR_BLUE, COLOR_BLACK);
  init_pair(3,COLOR_WHITE, COLOR_BLACK);
  init_pair(5,COLOR_MAGENTA, COLOR_BLACK);
  init_pair(6,COLOR_CYAN, COLOR_BLACK);
  bkgd(COLOR_PAIR(3));


}
Screen::~Screen(){
  endwin();
}
void Screen::draw(){
  drawTable();
  for(int i=0;i<5;i++){
    mvprintw(philoY[i],philoX[i],"%s",philoState[i].c_str());
    move(forkY[i],forkX[i]);
    addch(forkState[i]);
  }
}
void Screen::defaultScreen(Philosopher** philosophersW, Fork** forksW){

  draw();
  int c;
nodelay(stdscr, TRUE);
for(;;){
  if((c = getch())!=27){
    for(int i=0;i<5;i++){
   State s = philosophersW[i]->state;
    if(s == Eat){

          attron(COLOR_PAIR(4));
          mvprintw(philoY[i],philoX[i],"%s",philoState[i].c_str());
          attroff(COLOR_PAIR(4));

    }
    else if(s == Think){
      attron(COLOR_PAIR(5));
      mvprintw(philoY[i],philoX[i],"%s",philoState[i].c_str());
      attroff(COLOR_PAIR(5));
    }
    else{
      mvprintw(philoY[i],philoX[i],"%s",philoState[i].c_str());
    }
    drawProgress(s,philosophersW[i]->currentProgress,i);
  for(int i=0;i<5;i++){
    ForkInUse(i,forksW[i]->getState());
  }



  timeout(250);
  }
}
else {
  return;
}
}
}
void Screen::ForkInUse(int forkId,bool isFree){

  move(forkY[forkId],forkX[forkId]);

  if(!isFree){
    attron(COLOR_PAIR(1));
  }
  else{
    attron(COLOR_PAIR(2));
  }

  addch(forkState[forkId]);


  attroff(COLOR_PAIR(2));
  attroff(COLOR_PAIR(1));



  }


void Screen::drawProgress(State s, int progressSteps, int phiId){

    if(s == Eat ){
      mvprintw(13+phiId,25,"%s : jedzenie: %d%s",philoState[phiId].c_str(),10*(progressSteps+1),"%");
      attron(COLOR_PAIR(4));

    }
    else if(s == Think){
      mvprintw(13+phiId,25,"%s : myslenie: %d%s",philoState[phiId].c_str(),10*(progressSteps+1),"%");
      attron(COLOR_PAIR(5));
    }
    else if(s == WaitForForks){
      mvprintw(13+phiId,25,"%s : oczekiwanie",philoState[phiId].c_str());
      refresh();
    }
    clrtoeol();

    attroff(COLOR_PAIR(4));
    attroff(COLOR_PAIR(5));
    attron(COLOR_PAIR(5));
    for(int i = 24; i <= 54; i++){
    mvprintw(12,i,"-");
    mvprintw(18,i,"-");
    }
    for(int i = 13; i <= 17; i++){
    mvprintw(i,24,"-");
    mvprintw(i,54,"-  ");
    }
    attroff(COLOR_PAIR(5));
    clrtoeol();

    move(18,0);
    attron(COLOR_PAIR(3));
    printw("Legenda: ");
    attroff(COLOR_PAIR(3));

    move(19,0);
    attron(COLOR_PAIR(5));
    printw("- Myslenie");
    attroff(COLOR_PAIR(5));

    move(20,0);
    attron(COLOR_PAIR(4));
    printw("- Jedzenie");
    attroff(COLOR_PAIR(4));

    move(21,0);
    attron(COLOR_PAIR(3));
    printw("- Oczekiwanie");
    attroff(COLOR_PAIR(3));

    move(22,0);
    attron(COLOR_PAIR(2));
    printw("- Wolny widelec");
    attroff(COLOR_PAIR(2));

    move(23,0);
    attron(COLOR_PAIR(1));
    printw("- Zajety widelec");
    attroff(COLOR_PAIR(1));

}
void Screen::drawTable(){
  attron(COLOR_PAIR(6));
  for(int i = 28; i <= 48; i++){
  mvprintw(1,i,"_");
  mvprintw(9,i,"_");
  }
  mvprintw(2, 27, "/");
  mvprintw(3, 26, "/");
  mvprintw(4, 25, "/");
  mvprintw(5, 24, "|");
  mvprintw(6, 24, "|");
  mvprintw(7, 25, "\\");
  mvprintw(8, 26, "\\");
  mvprintw(9, 27, "\\");
  mvprintw(2, 50, "\\");
  mvprintw(3, 51, "\\");
  mvprintw(4, 52, "\\");
  mvprintw(5, 53, "|");
  mvprintw(6, 53, "|");
  mvprintw(7, 52, "/");
  mvprintw(8, 51, "/");
  mvprintw(9, 50, "/");

  attroff(COLOR_PAIR(6));
}
