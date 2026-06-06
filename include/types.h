#pragma once
#include <string>
#include <vector>


struct Order {
    unsigned int id;
    double weight;
    std::string zone;

};

struct Truck {
    unsigned int id;
    double max_capacity;
    double current_weight = 0.0;
    std::string zone;
    std::string base_point;
};


struct Assignment {
    unsigned int order_id;
    unsigned int truck_id;
};

struct Plan {
    std::vector<Assignment> assignments;
    std::vector<Order>unassigned_orders;
};