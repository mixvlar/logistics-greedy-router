#pragma once
#include <vector>
#include "../../include/types.h"




void add_to_memory(const Order& order, std::vector<Order>& orders_vector);
void add_to_memory(const Truck& truck, std::vector<Truck>& trucks_vector);

Plan build_plan_greedy(std::vector<Order>& orders, std::vector<Truck>& trucks);
