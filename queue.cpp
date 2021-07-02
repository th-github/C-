// circularbuffer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>
#include <stdexcept>
using namespace std;

template <class T> class RingBuffer {
private:
    unique_ptr<T[]> buffer;
    size_t head = 0, tail = 0, max_size;
    size_t counts = 0;
    T empty_item = 0;
public:
    RingBuffer<T>(size_t size)
        : buffer(unique_ptr<T[]> (new T[size])), 
          max_size(size), counts(0), empty_item(0) 
    {
        buffer[head] = empty_item;
    };
    void enqueue(T item)
    {
        uint16_t next = 0;
        next = head + 1;

        //if (next != tail)
        {
            buffer[head] = item;
            head = next;
            counts++;
        }
        if (next >= max_size)
            counts = max_size;
    }
    bool dequeue(T& item)
    {
        uint16_t next = 0;

        //if (head == tail)
        //    return -1;
        next = tail + 1;
        if (next >= max_size)
            next = 0;
        item = buffer[tail];
        tail = next;

        return 0;
    }

    bool isEmpty() { return (head == tail); }
    bool isFull() { 
        return (head >= max_size);
    }
    size_t itemCounts()
    {
        return counts;
    }
};

int main()
{
    cout << "Ring Buffer\n";
    size_t max = 5;
    static RingBuffer<uint32_t> rb(max);
    cout << "Size of the buffer: " << max << endl;
       
    uint32_t x = 2;
        
    rb.enqueue(x);
    cout << "item added: " << x << endl;
    x = 0;
    rb.enqueue(x);
    cout << "item added: " << x << endl;
    x = 65536;
    rb.enqueue(x);
    cout << "item added: " << x << endl;
    x = 1;
    rb.enqueue(x);
    cout << "item added: " << x << endl;

    x = 1234;
    rb.enqueue(x);
    cout << "item added: " << x << endl;
    x = 6;
    rb.enqueue(x);
    cout << "item added: " << x << endl;

    x = 32768;
    rb.enqueue(x);
    cout << "item added: " << x << endl;

    cout << "number of items in buffer: " << rb.itemCounts() << endl;

    x = 0;
    if (!rb.dequeue(x))
        cout << "item retrieved: " << x << endl;

    if(!rb.dequeue(x))
        cout << "item retrieved: " << x << endl;

    if(!rb.dequeue(x))
        cout << "item retrieved: " << x << endl;

    if(!rb.dequeue(x))
        cout << "item retrieved: " << x << endl;
   
    cout << "number of items in buffer: " << rb.itemCounts() << endl;

    if (!rb.dequeue(x))
        cout << "item retrieved: " << x << endl;
    if (!rb.dequeue(x))
        cout << "item retrieved: " << x << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
