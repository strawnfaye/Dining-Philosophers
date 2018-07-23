// S. Faye Strawn
// COP4520 - Spring 2018
// Programming Assignment #1: Dining Philosophers

#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>
#include <chrono>

void run();

class Chopstick
{
    std::mutex chop;

public:
    void lock()
    {
        chop.lock();
    }

    void unlock()
    {
        chop.unlock();
    }
};

class Philosopher
{
    std::atomic_bool runFlag;
    std::thread *will;
    Chopstick *leftChop;
    Chopstick *rightChop;
    
    void run()
    {
        while(runFlag)
        {
            std::cout << std::this_thread::get_id() << " is now thinking\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000 + 1));
            std::cout << std::this_thread::get_id() << " is now hungry\n";
            leftChop->lock();
            rightChop->lock();
            std::cout << std::this_thread::get_id() << " is now eating\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000 + 1));
            rightChop->unlock();
            leftChop->unlock();
        }
    }

public:
    Philosopher(Chopstick *leftChop, Chopstick *rightChop)
    {
        this->leftChop = leftChop;
        this->rightChop = rightChop;
        runFlag = true;
        will = new std::thread(&Philosopher::run, this);
    }

    void terminate()
    {
        runFlag = false;
        will->join();
    }

    ~Philosopher()
    {
        delete will;
    }
};

int main()
{
    int num = 5;
    std::vector<Philosopher*> theGang;
    std::vector<Chopstick> chopstix(num);

    for(int i = 0; i < num; i++)
    {
        theGang.push_back(new Philosopher(&chopstix[i], &chopstix[(i + 1) % num]));
    }

    while(std::cin.get() != 'n');

    for(Philosopher* p : theGang)
    {
        p->terminate();
        delete p;
    }

}