#ifndef ENTITY_MODEL_H
#define ENTITY_MODEL_H

#include <string>

struct Order {
    int orderId;
    std::string customerName;
    double totalValue;
    std::string paymentStatus;
    std::string shippingClass;

    Order()
        : orderId(0), customerName(""), totalValue(0.0),
          paymentStatus("Pending"), shippingClass("Standard") {}

    Order(int id, const std::string& customer, double total,
          const std::string& payment, const std::string& shipping)
        : orderId(id), customerName(customer), totalValue(total),
          paymentStatus(payment), shippingClass(shipping) {}
};

#endif
