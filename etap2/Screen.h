#include <vector>
#include <string>
#include "Philosopher.h"

using namespace std;

class Screen
{
public:
  Screen();
  ~Screen();
  void draw();
  void defaultScreen(Philosopher** philosophersW, Fork** forksW);
  void ForkInUse(int forkId,bool isFree);
  void drawProgress(State s, int progressSteps, int phiId);
  void drawTable();
private:
  int philospoherId;
  int forkId;
  string philoState[5]={"Sokrates","Platon","Arystoteles","Zenon","Heraklit"};
  int philoY[5]={0,5,5,10,10};
  int philoX[5]={35,17,54,30,40};
  char forkState[5]={'Y','Y','Y','Y','Y'};
  int forkY[5]={2,2,6,8,6};
  int forkX[5]={32,45,47,37,30};


};
