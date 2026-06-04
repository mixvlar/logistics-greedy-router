#include "distribution.h"
#include <algorithm>
#include <vector>

using namespace std;


void add_to_memory(const Order& order, vector<Order>& orders_vector) {
    orders_vector.push_back(order);
}

void add_to_memory(const Truck& truck, vector<Truck>& trucks_vector) {
    trucks_vector.push_back(truck);
}

Plan build_plan_greedy(vector<Order>& orders, vector<Truck>& trucks){
    Plan plan;
    sort(orders.begin(), orders.end(), [](const Order& a, const Order& b){return a.weight > b.weight;});

    for (const auto& order  : orders){
        bool assigned = false;
        for (auto& truck : trucks){
            if ((truck.zone == order.zone) && (truck.current_weight + order.weight <= truck.max_capacity)){
                truck.current_weight += order.weight;
                plan.assignments.push_back({order.id, truck.id});
                assigned = true;
                break;
            }
        }
        if (!assigned)
            plan.unassigned_orders.push_back(order);
    }
    return plan;
}