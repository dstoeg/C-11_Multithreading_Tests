#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <string>
#include <thread>
#include <mutex>

static std::mutex mConsoleLock;

#define MIN_TIME_THINKING 1
#define MAX_TIME_THINKING 10

#define MIN_TIME_EATING 1
#define MAX_TIME_EATING 10

#define MEAL_COUNT 10

class Philosopher
{
public:
    Philosopher(std::string const& name, std::mutex * left, std::mutex * right);
    void doWaitToEat();

private:
    std::string mName;
    std::mutex * mLeftFork;
    std::mutex * mRightFork;
    size_t mMealCount;

    void doSayStartEating();
    void doEat();
    void doWaitRandomTime();
    void doSayStartThinking();
    void doThink();
    void doSayFinished();
    void lockedPrint(std::string const& str);

};

#endif // PHILOSOPHER_H
