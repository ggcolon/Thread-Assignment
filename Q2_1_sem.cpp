//Gerrado Colon
//Thread Assignment 
//4/15/2023

#include <iostream>
#include <thread>
#include <semaphore.h>
using namespace std;

sem_t sem;

void runMeFirst() {
    cout << "Run me first" << endl;
    sem_post(&sem);
}

void runMeSecond() {
    sem_wait(&sem);
    cout << "I run second" << endl;
}

int main() {
    // initialize the semaphore with 0
    sem_init(&sem, 0, 0);

    thread t1(runMeFirst);
    thread t2(runMeSecond);

    t1.join();
    t2.join();

    sem_destroy(&sem);

    return 0;
}
