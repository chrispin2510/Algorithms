#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <string>

typedef struct Node {
    char symbol;
    int strength;
    int depth;
    Node * lchild;
    Node * rchild;
} * Node_T; 

class Heap 
{
public:
    Heap(int capacity = 1);
    ~Heap();
    Heap(const Heap&);
    Heap& operator=(const Heap&);
    void set_capacity(int);
    int get_size() const;
    void insert_max_heap(const Node_T&);
    void insert_min_heap(const Node_T&);
    void create_max_heap(const void *); 
    void create_min_heap(const void *);
    Node_T delete_max_heap();
    Node_T delete_min_heap();
    void heap_sort();
    void output() const;
private:
    int capacity;
    int size;
    Node_T *heap;
    void create_heap();
};

Heap::Heap(int capacity)
{
    set_capacity(capacity);
    create_heap(); 
    size = 0;
}

Heap::~Heap() 
{
    delete[] heap;
}

Heap::Heap(const Heap& x)
{
    set_capacity(x.capacity);
    create_heap();
    if (size > x.size)  {
        for (int i = 0; i < x.size; i++)
            heap[i] = x.heap[i];
    }
    else {
        for (int i = 0; i < size; i++)
            heap[i] = x.heap[i];
    }
}

Heap& Heap::operator=(const Heap& x)
{
    if (this == &x) 
        return *this;
    if (size >= x.size) {
        for (int i = 0; i < x.size; i++)
            heap[i] = x.heap[i];
    }
    else {
        for (int i = 0; i < size; i++)
            heap[i] = x.heap[i];
    }
    return *this;
}

void Heap::set_capacity(int capacity)
{
    if (capacity <= 0)
        throw "The capacity of the heap should be > 0";
    this->capacity = capacity;
}

void Heap::create_heap()
{
    heap = new Node_T[capacity];
}

void Heap::insert_max_heap(const Node_T& x)
{
    if (size == capacity) {
        std::cerr << "Heap is full. \n";
        exit(EXIT_FAILURE);
    }
    int i = ++size;
    while ((i != 1) && (x->strength > heap[i/2]->strength)) {
        heap[i] = heap[i/2];
        i /= 2;
    }
    heap[i] = x;
}

void Heap::insert_min_heap(const Node_T& x)
{
    if (size == capacity) {
        std::cerr << "Heap is full. \n";
        exit(EXIT_FAILURE);
    }
    int i = ++size;
    while ((i != 1) && (x->strength < heap[i/2]->strength)) {
        heap[i] = heap[i/2];
        i /= 2;
    }
    heap[i] = x;
}

Node_T Heap::delete_max_heap()
{
    if (!size) {
        std::cerr << "The heap is empty.\n";
        exit(EXIT_FAILURE);
    }
    Node_T item = heap[1];
    Node_T temp = heap[size--];
    int p = 1;
    int i = 2;
    while (i <= size) {
        if ((i < size) && (heap[i]->strength < heap[i+1]->strength))
            i++;
        if (temp->strength >= heap[i]->strength) break;
        heap[p] = heap[i];
        p = i;
        i *= 2;
    }
    heap[p] = temp;
    return item;
}

Node_T Heap::delete_min_heap()
{
    if (!size) {
        std::cerr << "The heap is empty. \n";
        exit(EXIT_FAILURE);
    } 
    Node_T item = heap[1];
    Node_T temp = heap[size--];
    int p = 1;
    int i = 2;
    while (i <= size) {
        if ((i < size) && (heap[i]->strength > heap[i+1]->strength))
            i++;
        if (temp->strength <= heap[i]->strength) break;
        heap[p] = heap[i];
        p = i;
        i *= 2;
    }
    heap[p] = temp;
    return item;
}

void Heap::heap_sort()
{
    while  (size > 1) {
        Node_T temp = delete_max_heap();
        heap[size+1] = temp; 
    }
}

void Heap::output() const
{
    for (int i = 1; i <= size; i++) {
        if (i > 1 && i <= size) 
            std::cout << ", ";
        std::cout << heap[i];
    }
    std::cout << std::endl;
}

void Heap::create_max_heap(const void * a)
{
    for (int i = 0; i < capacity-1; i++)
        insert_max_heap(((Node_T*)a)[i]);
}

void Heap::create_min_heap(const void * a)
{
    for (int i = 0; i < capacity-1; i++)
        insert_min_heap(((Node_T*)a)[i]);
}

#endif // HEAP_