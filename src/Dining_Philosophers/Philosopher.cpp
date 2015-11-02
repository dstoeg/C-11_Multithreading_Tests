#include "Philosopher.h"
#include "RandomGen.h"
#include <unistd.h>

#include <iostream>

using namespace std;


Philosopher::Philosopher(const std::string &name, std::mutex * left, std::mutex * right)
{
    mName = name;
    mLeftFork = left;
    mRightFork = right;
    mMealCount = 0;
}


void Philosopher::doWaitToEat()
{
    lockedPrint(mName + " starts eating and thinking");

    do {
        if (mLeftFork->try_lock() && mRightFork->try_lock()) {

            doSayStartEating();
            doEat();
            mMealCount++;

            mLeftFork->unlock();
            mRightFork->unlock();

            doSayStartThinking();
            doThink();
        }
        else {

            mLeftFork->unlock();
            mRightFork->unlock();
            doWaitRandomTime();
        }

    } while (mMealCount < MEAL_COUNT);

    doSayFinished();

}

void Philosopher::doSayStartEating()
{
    lockedPrint(mName + " eats meal #" + std::to_string(mMealCount));
}

// done
void Philosopher::doEat()
{
    sleep(0.1 * rgen::GetRandVal(MIN_TIME_EATING, MAX_TIME_EATING));
}

void Philosopher::doWaitRandomTime()
{
    sleep(0.1 * rgen::GetRandVal(MIN_TIME_EATING, MAX_TIME_EATING));
}

// done
void Philosopher::doSayStartThinking()
{
    lockedPrint(mName + " starts thinking for a while");
}

// done
void Philosopher::doThink()
{
    sleep(0.1 * rgen::GetRandVal(MIN_TIME_THINKING, MAX_TIME_THINKING));
}

// done
void Philosopher::doSayFinished()
{
    lockedPrint(mName + " finished all meals");
}

// done
void Philosopher::lockedPrint(const string &str)
{
    mConsoleLock.lock();
    cout << str << endl;
    mConsoleLock.unlock();
}

