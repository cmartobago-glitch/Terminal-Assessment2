#include "LinkedListEngine.h"

#include <iomanip>
#include <iostream>

LinkedListEngine::LinkedListEngine() : head(nullptr), tail(nullptr), count(0) {}

LinkedListEngine::~LinkedListEngine() {
    clear();
}

bool LinkedListEngine::isEmpty() const {
    return head == nullptr;
}

std::size_t LinkedListEngine::size() const {
    return count;
}

LinkedListEngine::Node* LinkedListEngine::findNode(int orderId) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.orderId == orderId) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

bool LinkedListEngine::containsId(int orderId) const {
    return findNode(orderId) != nullptr;
}

void LinkedListEngine::linkBetween(Node* previous, Node* node, Node* next) {
    node->prev = previous;
    node->next = next;

    if (previous != nullptr) {
        previous->next = node;
    } else {
        head = node;
    }

    if (next != nullptr) {
        next->prev = node;
    } else {
        tail = node;
    }
    ++count;
}

void LinkedListEngine::unlinkAndDelete(Node* node) {
    if (node == nullptr) {
        return;
    }

    if (node->prev != nullptr) {
        node->prev->next = node->next;
    } else {
        head = node->next;
    }

    if (node->next != nullptr) {
        node->next->prev = node->prev;
    } else {
        tail = node->prev;
    }

    delete node;
    node = nullptr;
    --count;
}

bool LinkedListEngine::insertHead(const Order& order) {
    if (containsId(order.orderId)) {
        return false;
    }

    Node* node = new Node(order);
    linkBetween(nullptr, node, head);
    return true;
}

bool LinkedListEngine::insertTail(const Order& order) {
    if (containsId(order.orderId)) {
        return false;
    }

    Node* node = new Node(order);
    linkBetween(tail, node, nullptr);
    return true;
}

bool LinkedListEngine::insertSortedById(const Order& order) {
    if (containsId(order.orderId)) {
        return false;
    }

    Node* current = head;
    while (current != nullptr && current->data.orderId < order.orderId) {
        current = current->next;
    }

    if (current == nullptr) {
        return insertTail(order);
    }

    Node* node = new Node(order);
    linkBetween(current->prev, node, current);
    return true;
}

bool LinkedListEngine::removeById(int orderId) {
    Node* node = findNode(orderId);
    if (node == nullptr) {
        return false;
    }

    unlinkAndDelete(node);
    return true;
}

const Order* LinkedListEngine::searchById(int orderId) const {
    Node* node = findNode(orderId);
    return node == nullptr ? nullptr : &node->data;
}

bool LinkedListEngine::updateOrder(int orderId, const std::string& customerName,
                                   double totalValue, const std::string& paymentStatus,
                                   const std::string& shippingClass) {
    Node* node = findNode(orderId);
    if (node == nullptr) {
        return false;
    }

    node->data.customerName = customerName;
    node->data.totalValue = totalValue;
    node->data.paymentStatus = paymentStatus;
    node->data.shippingClass = shippingClass;
    return true;
}

void LinkedListEngine::displayForward() const {
    if (isEmpty()) {
        std::cout << "\nNo orders in the registry.\n";
        return;
    }

    std::cout << "\nORDERS (head -> tail)\n";
    std::cout << std::left << std::setw(10) << "Order ID"
              << std::setw(24) << "Customer"
              << std::right << std::setw(12) << "Total"
              << std::left << std::setw(14) << "Payment"
              << std::setw(12) << "Shipping" << "\n";
    std::cout << std::string(72, '-') << "\n";

    const Node* current = head;
    while (current != nullptr) {
        std::cout << std::left << std::setw(10) << current->data.orderId
                  << std::setw(24) << current->data.customerName.substr(0, 22)
                  << std::right << std::setw(12) << std::fixed << std::setprecision(2)
                  << current->data.totalValue
                  << std::left << std::setw(14) << current->data.paymentStatus
                  << std::setw(12) << current->data.shippingClass << "\n";
        current = current->next;
    }
    std::cout << "Total orders: " << count << "\n";
}

void LinkedListEngine::displayBackward() const {
    if (isEmpty()) {
        std::cout << "\nNo orders in the registry.\n";
        return;
    }

    std::cout << "\nORDERS (tail -> head)\n";
    const Node* current = tail;
    while (current != nullptr) {
        std::cout << "ID: " << current->data.orderId
                  << " | Customer: " << current->data.customerName
                  << " | Total: " << std::fixed << std::setprecision(2)
                  << current->data.totalValue
                  << " | Payment: " << current->data.paymentStatus
                  << " | Shipping: " << current->data.shippingClass << "\n";
        current = current->prev;
    }
}

void LinkedListEngine::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head = nullptr;
    tail = nullptr;
    count = 0;
}
