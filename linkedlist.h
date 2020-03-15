/*
 Nicole Zhang
 nj3zhang
 */
#include <iostream>
#ifndef linkedlist_h
#define linkedlist_h
class Node {
public:
    int data{0};
    Node *next {nullptr};
    Node *prev {nullptr};
};

class linkedlist {
public:
    Node *list_head {nullptr};
    Node *list_tail {nullptr};
    int list_size {0};
    
    ~linkedlist();
    std::string enqueue_front(int i);
    std::string enqueue_back(int i);
    std::string dequeue_front();
    std::string dequeue_back();
    std::string clear();
    std::string front(int i);
    std::string back(int i);
    std::string empty();
    int size();
    void print();
    
};

class deque_empty{};
#endif /* linkedlist_h */
