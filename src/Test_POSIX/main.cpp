#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <string>
#include <vector>
#include <iterator>
#include <unistd.h>
#include <sstream>


using namespace std;

typedef std::vector<int> TVec;
typedef std::vector<int>::iterator TVecIter;

size_t const SIZE = 100;

pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;

struct thread_data{
   std::string name;
   TVecIter begin;
   TVecIter end;
};

void printThreadsafe(string const& text) {
    pthread_mutex_lock( &count_mutex );

    cout << text << endl;

    pthread_mutex_unlock( &count_mutex );
}

void * threadFunc(void * threadArg) {

    thread_data * data = reinterpret_cast<thread_data*>(threadArg);
    string str = data->name;
    TVecIter begin = data->begin;
    TVecIter end = data->end;

    while (begin != end) {
        std::stringstream ss;
        ss << str << ": " << (*begin);
        std::string s = ss.str();
        printThreadsafe((s));
        begin++;
        usleep(1000);
    }
    pthread_exit(NULL);
}



int main ()
{
    TVec myVec;

    for (size_t i=0; i<SIZE; ++i) {
        myVec.push_back(i);
    }

    TVecIter mid = myVec.begin() + myVec.size() / 2;



    const size_t NUM_THREADS = 2;

    struct thread_data data[NUM_THREADS];
    pthread_t threads[NUM_THREADS];

    thread_data data1;
    data1.begin = myVec.begin();
    data1.end = mid;
    data1.name = "thread1";
    data[0] = data1;

    thread_data data2;
    data2.begin = mid;
    data2.end = myVec.end();
    data2.name = "thread2";
    data[1] = data2;

    for(int i=0; i < NUM_THREADS; i++ ) {

        pthread_create(&threads[i], NULL, &threadFunc, (void *)&data[i]);
    }
    pthread_exit(NULL);
}
