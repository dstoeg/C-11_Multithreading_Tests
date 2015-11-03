# C-11_Multithreading_Tests
Some implementations of multithreaded programs in C++. Comparing C++11, Boost and WIN32 API for threading performance

Includes implementations of

- Thread creation test - multithreaded std::vector access (POSIX, WIN32 API, C++11 comparison)
- Multithreaded Matrix Multiplication (C++11)
- Dining Philosophers Problem (C++11)

Multithreaded Matrix Implementation:
Matrices are defined as classes, and only support symmetric forms. Types are implemented as templates and dimensions can be passed in CTor. Number of concurrent threads for multiplication are powers of 4 e.g. 4, 16, 64. Multiplication takes references to 2 given matrices and puts the result into a third matrix, which allows for maximum parallelism. Result matrix is divided into symmetric blocks.

Dining Philosophers Problem:
Implementation of a classic synchronization problem. 5 Philosophers are sitting at a table. Each philosopher has a plate in front of him and there are 5 forks on the table. All philosophers have to eat and think for a random time. To be able to eat, a philosopher needs 2 forks, which means they can't eat at the same time. Philosophers have to be able to eat and think with minimal waiting periods and maximal parallelism. It's important to avoid deadlocks (e.g. each philosopher grabs a fork and waits for the second one, which freezes the system).
For implementing this problem a class describing a philosopher was implemented. The class contains a method which defines the behaviour of the philosopher (eat and think for a random time, until a certain number of meals has been consumed). The forks, which are the shared resources that need to be synchronized are implemented as std::mutex objects. Every philosopher gets access to two references of these mutex objects. By using the std::try_lock() function it can be guaranteed that no deadlock or starvation can occur.


