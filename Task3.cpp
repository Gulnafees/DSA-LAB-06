#include <iostream>
using namespace std;

// Store information about each print request
struct Request {
    int id;
    int arrivalTime;
    int processingTime;
};

// Circular queue using a dynamically allocated array
class PrintQueue {
    Request* items;
    int capacity;
    int count;
    int frontIndex;
    int minCapacity;

public:
    PrintQueue(int size = 2) {
        capacity = size;
        minCapacity = size;
        items = new Request[capacity];
        count = 0;
        frontIndex = 0;
    }

    ~PrintQueue() {
        delete[] items;
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == capacity;
    }

    // Change capacity without losing any requests
    void resize(int newCapacity) {
        if (newCapacity < minCapacity)
            newCapacity = minCapacity;
        if (newCapacity < count)
            newCapacity = count;

        Request* newItems = new Request[newCapacity];

        // Copy requests in their correct FIFO order
        for (int i = 0; i < count; i++)
            newItems[i] = items[(frontIndex + i) % capacity];

        delete[] items;
        items = newItems;
        capacity = newCapacity;
        frontIndex = 0;

        cout << "Queue resized to: " << capacity << endl;
    }

    // Add a request to the rear
    void enqueue(Request x) {
        if (isFull())
            resize(capacity * 2);

        int rear = (frontIndex + count) % capacity;
        items[rear] = x;
        count++;

        cout << "Enqueued Request " << x.id << endl;
        display();
    }

    // Remove and return the front request
    Request dequeue() {
        Request x = items[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        count--;

        cout << "Dequeued Request " << x.id << endl;

        // Shrink when the queue is one-quarter full or less
        if (capacity > minCapacity && count <= capacity / 4)
            resize(capacity / 2);

        display();
        return x;
    }

    // Return the front request without removing it
    Request front() {
        return items[frontIndex];
    }

    // Display requests in FIFO order
    void display() {
        cout << "Queue: ";

        if (isEmpty()) {
            cout << "Empty";
        } else {
            for (int i = 0; i < count; i++) {
                int index = (frontIndex + i) % capacity;
                cout << items[index].id << " ";
            }
        }

        cout << "\nSize: " << count
             << ", Capacity: " << capacity << endl << endl;
    }
};

int main() {
    PrintQueue q(2);

    cout << "PRINT SERVER REQUEST SYSTEM\n\n";
    int n;
    cout << "Enter the number of print requests: ";
    if (!(cin >> n) || n <= 0) {
        cerr << "Please enter a positive number of requests." << endl;
        return 1;
    }

    // Read each request and add it to the queue
    for (int i = 0; i < n; i++) {
        Request request;
        cout << "Request " << i + 1 << " - enter ID, arrival time, and "
             << "processing time: ";
        if (!(cin >> request.id >> request.arrivalTime >> request.processingTime) ||
            request.arrivalTime < 0 || request.processingTime <= 0) {
            cerr << "Invalid request. Arrival time must be non-negative and "
                 << "processing time must be positive." << endl;
            return 1;
        }
        q.enqueue(request);
    }

    // Calculate waiting time while processing requests
    int currentTime = 0;
    int totalWaitingTime = 0;
    int processed = 0;

    cout << "PROCESSING REQUESTS\n\n";

    while (!q.isEmpty()) {
        Request r = q.front();

        // Wait until the request arrives if necessary
        if (currentTime < r.arrivalTime)
            currentTime = r.arrivalTime;

        int waitingTime = currentTime - r.arrivalTime;
        totalWaitingTime += waitingTime;

        cout << "Request ID: " << r.id << endl;
        cout << "Arrival Time: " << r.arrivalTime << endl;
        cout << "Processing Time: " << r.processingTime << endl;
        cout << "Waiting Time: " << waitingTime << endl;

        currentTime += r.processingTime;
        q.dequeue();
        processed++;
    }

    cout << "Average Waiting Time: "
         << (double)totalWaitingTime / processed << endl;

    return 0;
}
