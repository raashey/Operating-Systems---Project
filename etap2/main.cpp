#include <vector>
#include <iostream>
#include <ncurses.h>
#include "Screen.h"

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    //--------------------------Stworzenie obiektów-----------------------/
    Fork** forks = new Fork*[5];
    Screen scr = Screen();
    Philosopher** philosophers = new Philosopher*[5];
    for(int i=0;i<5;i++){
      forks[i] = new Fork(i);
    }
    for(int i=0;i<5;i++){
    if(i == 4){
      philosophers[i] = new Philosopher(i, forks[4], forks[0]);
      break;
    }
      philosophers[i] = new Philosopher(i, forks[i], forks[i+1]);
    }

    //---------------------------stworzenie wątków------------------------//
    std::thread threads[5];
    //----------------------------start cyklu----------------------------//
    for(int i=0;i<5;i++){
      threads[i] = std::thread(&Philosopher::start, philosophers[i]);
    }
    scr.defaultScreen(philosophers,forks);
    //----------------------------stop cyklu-----------------------------//
    for(int i=0;i<5;i++){
      philosophers[i]->stop();
    }
    //-----------------------czekanie na zakończenie wątków--------------//
    for(int i=0;i<5;i++){
      threads[i].join();
    }
    clear();
    refresh();
    endwin();
    return 0;
}
