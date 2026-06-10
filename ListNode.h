#pragma once
namespace collections {
template<typename T>
class ListNode {
private:  
    T value;
    ListNode<T>* nextNode;
    ListNode<T>* prevNode;
    
    template<typename U>
    friend class LinkedList;

public:
    explicit ListNode(T& val) : value(val), nextNode(nullptr), prevNode(nullptr) {}
};
}
