#include <pthread.h>
#include <iostream>
#include <mutex>
#include <condition_variable>
class Fork
{
    private:
        int id;
        std::mutex mtx;
        std::condition_variable var;
        bool state;
    public:

        Fork(int id);
        ~Fork();
        void take();
        void drop();
        bool getState();
        void setState(bool i);

    protected:
};
