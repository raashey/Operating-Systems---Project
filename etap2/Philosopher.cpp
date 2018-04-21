#include "Philosopher.h"
#include <iostream>
#include <ncurses.h>

using namespace std;

Philosopher::Philosopher(int pid,Fork* lf,Fork* rf)
{
  this->currentProgress = 0;
  this->phiId = pid;
  this->leftFork = lf;
  this->rightFork = rf;

}
Philosopher::~Philosopher(){

}
void Philosopher::start()
{
  this->running = true;
            while(running){

              int thinkingTime = randomTime();
              waiting(thinkingTime);
              state = WaitForForks;
              takeForks();
              state = Eat;
              int eatingTime = randomTime();
              waiting(eatingTime);
              dropForks();
              state = Think;


          }
}
void Philosopher::takeForks(){
  if(phiId == 1){
    leftFork->take();
    rightFork->take();
  }
  else{
    rightFork->take();
    leftFork->take();
  }


}
void Philosopher::dropForks(){

  if(phiId == 1){
    rightFork->drop();
    leftFork->drop();
  }
  else{
    leftFork->drop();
    rightFork->drop();
  }



}
int Philosopher::randomTime(){
  return (4000 + rand()%4000)/10;

}
void Philosopher::waiting(int time){
  for(currentProgress = 0; currentProgress < 10; currentProgress++){
  std::this_thread::sleep_for(std::chrono::milliseconds(time));
  }
  currentProgress=0;
}
void Philosopher::stop(){
  running = false;
}
int Philosopher::GetphiId(){
  return phiId;
}
void Philosopher::SetphiId(int i){
   phiId = i;
}
int Philosopher::getCurrentProgress(){
  return currentProgress;
}
bool Philosopher::getRunning(){
  return running;
}
void Philosopher::setRunning(bool x){
   running = x;
}
