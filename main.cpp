#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>

using namespace std;

vector<bool> forks;	//wektor widelców
mutex mtx;	//utworzenie mutexu
chrono::milliseconds eat(1000);	// ustalenie czasów jedzenia i myślenia
chrono::milliseconds think(3000);

void start_eating(int i){
	if(forks[i] == true){
	mtx.lock();	// otworzenie sekcji krytycznej
  cout<<"Philosopher "<<i+1<<" is eating.\n";
	mtx.unlock(); // zamknięcie sekcji krytycznej
	forks[i] = false;	// zajęcie konkretnego widelca
	this_thread::sleep_for(eat); // zatrzymanie wątku na określony czas
	forks[i] = true; // zwolnienie konkretnego widelca
	}
}

void start_thinking(int i){
	mtx.lock();
	cout<<"Philosopher "<<i+1<<" is thinking.\n";
	mtx.unlock();
	this_thread::sleep_for(think);
}

void update(int i){
	int cycle = 0;	// zmienna określająca ilość cykli
	while (cycle < 5){
		start_eating(i);
		start_thinking(i);
		cycle++;
	}
}

int main(){
	for(int i = 0; i < 5; i++)	//wypełnianie wektora wolnymi widelcami
		forks.push_back(true);
	thread philosophers[5];
	for(int i = 0; i < 5; i++)
		philosophers[i] = thread(update, i);	//utworzenie wątków
	for(int i = 0; i < 5; i++)
		philosophers[i].join();	//czekanie na zakończenie wątków
	return 0;

}
