//Gerrado Colon
//Thread Assignment 
//4/15/2023

#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <random>
#include <string>

using namespace std;


// Define the structure of request
struct requestStructure {
    int request_id;
    string ip_address;
    string page_requested;
};

// Define the web pages
string webPages[10] = {"google.com", "yahoo.com", "facebook.com", "twitter.com", "linkedin.com", "reddit.com", "amazon.com", "wikipedia.org", "instagram.com", "netflix.com"};

// Define the shared data structures
queue<requestStructure> msg_queue;
int request_counter = 0;

// Define the mutex and conditional variable
mutex mtx;
condition_variable cv;

// Function to simulate receiving requests from clients
void listen() {
    // Define a random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 3);

    // Continuously generate requests
    while (true) {
        // Sleep for a random period of time
        this_thread::sleep_for(chrono::seconds(dis(gen)));

        // Generate a request
        requestStructure req;
        req.request_id = request_counter++;
        req.ip_address = "";
        req.page_requested = webPages[rand() % 10];

        // Lock the mutex and add the request to the queue
        unique_lock<mutex> lck(mtx);
        msg_queue.push(req);

        // Notify one thread to consume the request
        cv.notify_one();
    }
}

// Function to simulate processing requests
void do_request(int id) {
    while (true) {
        // Lock the mutex and wait for a request
        unique_lock<mutex> lck(mtx);
        while (msg_queue.empty()) {
            cv.wait(lck);
        }
        requestStructure req = msg_queue.front();
        msg_queue.pop();

        // Unlock the mutex
        lck.unlock();

        // Process the request
        cout << "Thread " << id << " completed request " << req.request_id << " requesting webpage " << req.page_requested << endl;
    }
}

int main() {
    // Create the listener thread
    thread listener(listen);

    // Create multiple request processing threads
    const int num_threads = 5;
    thread threads[num_threads];
    for (int i = 0; i < num_threads; i++) {
        threads[i] = thread(do_request, i);
    }

    // Wait for all threads to finish
    listener.join();
    for (int i = 0; i < num_threads; i++) {
        threads[i].join();
    }

    return 0;
}