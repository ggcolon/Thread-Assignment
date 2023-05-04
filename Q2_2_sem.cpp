//Gerrado Colon
//Thread Assignment 
//4/15/2023

#include <iostream>
#include <thread>
#include <semaphore.h>
using namespace std;

sem_t sem_first, sem_second;

void runMeFirst() {
    cout << "Run me first" << endl;
    sem_post(&sem_first);
}

void runMeSecond() {
    sem_wait(&sem_first);
    cout << "I run second" << endl;
    sem_post(&sem_second);
}

void runMeThird() {
    sem_wait(&sem_second);
    cout << "I run third" << endl;
}

int main() {
    // initialize the semaphores with 0
    sem_init(&sem_first, 0, 0);
    sem_init(&sem_second, 0, 0);

    thread t1(runMeFirst);
    thread t2(runMeSecond);
    thread t3(runMeThird);

    t1.join();
    t2.join();
    t3.join();

    sem_destroy(&sem_first);
    sem_destroy(&sem_second);

    return 0;
}
