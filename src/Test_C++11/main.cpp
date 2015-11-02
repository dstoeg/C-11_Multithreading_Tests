#include <string>
#include <thread>
#include <vector>
#include <iostream>
#include <iterator>
#include <unistd.h>


using namespace std;

typedef std::vector<int> TVec;
typedef std::vector<int>::iterator TVecIter;

size_t const SIZE = 100;


void threadFunc(std::string const& threadName, TVecIter begin, TVecIter end) {

    while (begin != end) {
        cout << threadName << ": " << (*begin) << endl;
        begin++;
        usleep(1000);
    }
}


int main()
{
    TVec myVec;

    for (size_t i=0; i<SIZE; ++i) {
        myVec.push_back(i);
    }

    TVecIter mid = myVec.begin() + myVec.size() / 2;
    std::thread t1(threadFunc, "thread1", myVec.begin(), mid);
    std::thread t2(threadFunc, "thread2", mid, myVec.end());
    t1.join();
    t2.join();


}
