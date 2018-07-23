# Dining-Philosophers
Multi-threaded "dining philosophers" problem.

This program is written in C++. Compilation instructions are for OSX.

Version 1:

From command prompt-
To compile:
g++ -std=c++11 diningphv1.cpp -o a.out

To run:
./a.out

To end program:
type 'n' and hit 'enter'.

Description:
In my program, I implement a Philosopher class and a Chopstick class. The Chopstick class has a mutex variable, chop, and lock() and unlock() functions to control the mutex. The Philosopher class has an atomic boolean runFlag to provide a condition on which the thread's loop will run, a left chopstick, a right chopstick, and the philosopher's "will" - his thread. The thread's run() function is implemented inside of the Philosopher class since each Philosopher's thread performs the function in general.
The program performs as such: a vector of 5 chopsticks is created, then a vector for philosophers ("theGang") is formed by creating 5 Philosophers and assigning to them a left and right chopstick using simple array math, so that each adjacent philosopher is "sharing" a chopstick between them. When a Philosopher is created, its constructor starts a thread running the run() function.
Now all 5 threads are running the run() function, behaving as follows: while runFlag is true, the philosopher thinks for an arbitrary amount of time, simulated by having the thread sleep for a randomly generated amount of time. Next, the philosopher becomes "hungry", and performs a lock() on both chopsticks (http://en.cppreference.com/w/cpp/thread/lock). The philosopher then "eats" for an arbitrary amount of time, then unlocks the chopstick mutexes in LIFO order. The cycle repeats, starting from thinking, until runFlag is marked false.
In this implementation, it is impossible for two philosopher to hold the same chopstick at the same time because of the lock() on the mutexes.
In main(), line 80 handles the halt condition input of 'n' from standard n by behaving as its own thread, cycling keeping the program from progressing to the next line until 'n' is entered. After 'n' is entered, the threads are terminated by marking the runFlag as false. The threads each finish their process in the current loop iteration and then are deleted, and the program ends.

Version 2:

From command prompt-
To compile:
g++ -std=c++11 diningphv2.cpp -o a.out

To run:
./a.out

To end program:
type 'n' and hit 'enter'.

Description:
This program is identical to version 1 except that its run() function is modified to ensure that the program never reaches a state where philosophers are deadlocked. ((((After entering the loop, the thread is forced to sleep for an random amount of time. This decreases the likelihood that two or more threads will begin their processes simultaneously. ))))
The chopstick mutexes are locked without deadlock, then lock_guard() is used to ensure that both already-locked mutexes are unlocked at the end of scope, when the current loop ends after the arbitrary eating time (http://en.cppreference.com/w/cpp/thread/lock_tag).

Version 3:

From command prompt-
To compile:
g++ -std=c++11 diningphv3.cpp -o a.out

To run:
./a.out

To end program:
type 'n' and hit 'enter'.

Description:
Only one line of code was modified from version 2 to ensure that no philosopher ever starves. After entering the loop, the thread is forced to sleep for a set, arbitrary amount of time (in this simulation, 250 milliseconds). This minor change means that every philosopher must take a break after eating, not long enough to starve, but long enough to give the next hungry philosopher a chance to eat. This felt like the most efficient way to eliminate greediness without any communication between the philosophers.

Version 4:

From command prompt-
To compile:
g++ -std=c++11 diningphv4.cpp -o a.out

To run:
./a.out

Then input the number of philosophers you wish to dine.

To end program:
type 'n' and hit 'enter'.

Description:
The only change to this version is that it takes any number of philosophers from standard input and creates that many philosophers and chopsticks. The algorithm in version 3 still holds for this condition.
