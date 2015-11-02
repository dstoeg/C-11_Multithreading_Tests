#include<iostream>
#include<conio.h>
#include<vector>
#include<iterator>
#include<Windows.h>
#include<sstream>
#include <cstdlib>

using namespace std;

typedef std::vector<int> TVec;
typedef std::vector<int>::iterator TVecIter;

size_t const cSIZE = 100;

struct thread_data {
	std::string name;
	TVecIter begin;
	TVecIter end;
};

DWORD WINAPI ThreadFunc(void * arg) {
	thread_data * data = reinterpret_cast<thread_data*>(arg);

	while (data->begin != data->end) {
		// print
		cout << data->name << ": " << (*data->begin) << endl;
		data->begin++;
		Sleep(10);
	}
	return 0;
}

int main() {

	TVec myVec;

	for (size_t i = 0; i<cSIZE; ++i) {
		myVec.push_back(i);
	}

	TVecIter mid = myVec.begin() + myVec.size() / 2;

	thread_data data1;
	data1.begin = myVec.begin();
	data1.end = mid;
	data1.name = "thread1";

	thread_data data2;
	data2.begin = mid;
	data2.end = myVec.end();
	data2.name = "thread2";


	DWORD Thread1Id = 0;
	DWORD Thread2Id = 0;
	HANDLE ThreadHandle1 = CreateThread(0, 0, ThreadFunc, (LPVOID)&data1, 0, &Thread1Id);
	HANDLE ThreadHandle2 = CreateThread(0, 0, ThreadFunc, (LPVOID)&data2, 0, &Thread2Id);

	_getch();


	CloseHandle(ThreadHandle1);
	CloseHandle(ThreadHandle2);

	return 0;
}
