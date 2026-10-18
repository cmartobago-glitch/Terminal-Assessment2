#ifndef LINKED_LIST_ENGINE_H
#define LINKED_LIST_ENGINE_H

#include "EntityModel.h"
#include <cstddef>

class LinkedListEngine {
private:
    struct Node {
        Order data;
        Node* prev;
        Node* next;

        explicit Node(const Order& order)
            : data(order), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    std::size_t count;

    Node* findNode(int orderId) const;
    bool containsId(int orderId) const;
    void linkBetween(Node* previous, Node* node, Node* next);
    void unlinkAndDelete(Node* node);


    LinkedListEngine(const LinkedListEngine&);
    LinkedListEngine& operator=(const LinkedListEngine&);

public:
    LinkedListEngine();
    ~LinkedListEngine();

    bool isEmpty() const;
    std::size_t size() const;

    bool insertHead(const Order& order);
    bool insertTail(const Order& order);
    bool insertSortedById(const Order& order);

    bool removeById(int orderId);
    const Order* searchById(int orderId) const;
    bool updateOrder(int orderId, const std::string& customerName,
                     double totalValue, const std::string& paymentStatus,
                     const std::string& shippingClass);

    void displayForward() const;
    void displayBackward() const;
    void clear();
};

#endif
