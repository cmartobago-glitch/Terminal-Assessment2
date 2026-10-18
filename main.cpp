#include "LinkedListEngine.h"

#include <iostream>
#include <limits>
#include <string>

namespace {
    int readInt(const std::string& prompt) {
        int value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
            std::cout << "Invalid input. Please enter a whole number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    double readDouble(const std::string& prompt) {
        double value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value && value >= 0.0) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
            std::cout << "Invalid amount. Enter a number that is zero or greater.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::string readText(const std::string& prompt) {
        std::string value;
        std::cout << prompt;
        std::getline(std::cin, value);
        return value;
    }

    Order readOrder() {
        int id = readInt("Order ID: ");
        std::string customer = readText("Customer name: ");
        double total = readDouble("Total value: ");
        std::string payment = readText("Payment status (Paid/Pending/Failed): ");
        std::string shipping = readText("Shipping class (Express/Standard/Eco): ");

        if (payment.empty()) payment = "Pending";
        if (shipping.empty()) shipping = "Standard";
        return Order(id, customer, total, payment, shipping);
    }

    void showMenu() {
        std::cout << "\n============================================\n"
                  << " E-COMMERCE ORDER FULFILLMENT & AUDIT ENGINE\n"
                  << " Linked List Registry Module\n"
                  << "============================================\n"
                  << "1. Add order at head\n"
                  << "2. Add order at tail\n"
                  << "3. Insert order sorted by ID\n"
                  << "4. Delete order by ID\n"
                  << "5. Search order by ID\n"
                  << "6. Update order\n"
                  << "7. Display forward\n"
                  << "8. Display backward\n"
                  << "9. Show order count\n"
                  << "10. Clear all orders\n"
                  << "0. Exit\n";
    }
}

int main() {
    LinkedListEngine orders;
    bool running = true;

    while (running) {
        showMenu();
        int choice = readInt("Choose an option: ");

        switch (choice) {
        case 1:
        case 2:
        case 3: {
            Order order = readOrder();
            bool success = false;
            if (choice == 1) success = orders.insertHead(order);
            else if (choice == 2) success = orders.insertTail(order);
            else success = orders.insertSortedById(order);

            if (success) std::cout << "Order added successfully.\n";
            else std::cout << "That Order ID already exists. IDs must be unique.\n";
            break;
        }
        case 4: {
            int id = readInt("Enter Order ID to delete: ");
            std::cout << (orders.removeById(id) ? "Order deleted.\n" : "Order ID not found.\n");
            break;
        }
        case 5: {
            int id = readInt("Enter Order ID to search: ");
            const Order* order = orders.searchById(id);
            if (order != nullptr) {
                std::cout << "Found order: ID " << order->orderId
                          << " | Customer: " << order->customerName
                          << " | Total: " << order->totalValue
                          << " | Payment: " << order->paymentStatus
                          << " | Shipping: " << order->shippingClass << "\n";
            } else {
                std::cout << "Order ID not found.\n";
            }
            break;
        }
        case 6: {
            int id = readInt("Enter Order ID to update: ");
            std::string customer = readText("New customer name: ");
            double total = readDouble("New total value: ");
            std::string payment = readText("New payment status (Paid/Pending/Failed): ");
            std::string shipping = readText("New shipping class (Express/Standard/Eco): ");
            if (orders.updateOrder(id, customer, total, payment, shipping)) {
                std::cout << "Order updated.\n";
            } else {
                std::cout << "Order ID not found.\n";
            }
            break;
        }
        case 7:
            orders.displayForward();
            break;
        case 8:
            orders.displayBackward();
            break;
        case 9:
            std::cout << "Total orders: " << orders.size() << "\n";
            break;
        case 10: {
            std::string confirm = readText("Type YES to delete all orders: ");
            if (confirm == "YES") {
                orders.clear();
                std::cout << "All orders cleared.\n";
            } else {
                std::cout << "Clear cancelled.\n";
            }
            break;
        }
        case 0:
            running = false;
            std::cout << "Exiting. Dynamically allocated nodes will be freed.\n";
            break;
        default:
            std::cout << "Invalid menu option. Choose 0 to 10.\n";
        }
    }

    return 0;
}
