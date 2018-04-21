#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
#include <atomic>
#include "Fork.h"


using namespace std;

enum State{
  Think,Eat,WaitForForks
};

class Philosopher
{
    public:
      Fork* leftFork;
      Fork* rightFork;
      volatile bool running;
      int currentProgress;
      std::atomic<State> state;
      int lvlOfStuffed;
      int phiId;


      Philosopher(int pid,Fork* lf,Fork* rf);
      ~Philosopher();
      void start();
      void takeForks();
      void dropForks();
      int randomTime();
      void stop();
      void waiting(int time);
      int GetphiId();
      void SetphiId(int i);
      int getCurrentProgress();
      bool getRunning();
      void setRunning(bool x);


};
