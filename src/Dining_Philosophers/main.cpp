#include <iostream>
#include <thread>
#include "Philosopher.h"

using namespace std;

int main()
{

    // create 5 forks as mutex
    mutex * fork1 = new mutex();
    mutex * fork2 = new mutex();
    mutex * fork3 = new mutex();
    mutex * fork4 = new mutex();
    mutex * fork5 = new mutex();


    // create 5 philisophers sharing the forks
    Philosopher * philosopher1 = new Philosopher("Philosopher 1", fork1, fork2);
    Philosopher * philosopher2 = new Philosopher("Philosopher 2", fork2, fork3);
    Philosopher * philosopher3 = new Philosopher("Philosopher 3", fork3, fork4);
    Philosopher * philosopher4 = new Philosopher("Philosopher 4", fork4, fork5);
    Philosopher * philosopher5 = new Philosopher("Philosopher 5", fork5, fork1);

    // start the threading

    thread * t1 = new thread(&Philosopher::doWaitToEat, *philosopher1);
    thread * t2 = new thread(&Philosopher::doWaitToEat, *philosopher2);
    thread * t3 = new thread(&Philosopher::doWaitToEat, *philosopher3);
    thread * t4 = new thread(&Philosopher::doWaitToEat, *philosopher4);
    thread * t5 = new thread(&Philosopher::doWaitToEat, *philosopher5);

    t1->join();
    t2->join();
    t3->join();
    t4->join();
    t5->join();


    cout << "all done" << endl;
    return 0;
}

