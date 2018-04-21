
#include "Fork.h"
#include <iostream>

using namespace std;

Fork::Fork(int id)
{
    this->id = id;
    this->state = true;
}

Fork::~Fork()
{
}
void Fork::take(){
    std::unique_lock<std::mutex> lock(mtx);
    var.wait(lock, [this](){return state == true;});
    state = false;
    lock.unlock();
}
void Fork::drop(){
    std::unique_lock<std::mutex> lock(mtx);
    state = true;
    var.notify_one();
    lock.unlock();
}
bool Fork::getState(){
  return state;
}
void Fork::setState(bool i){
  state = i;
}
