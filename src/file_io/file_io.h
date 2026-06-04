#pragma once
#include <string>
#include <vector>
#include "../../include/types.h"


bool load_orders(const std::string& filename, std::vector<Order>& orders);
bool load_trucks(const std::string& filename, std::vector<Truck>& trucks);

bool save_report(const std::string& filename, const Plan& plan, const std::vector<Truck>& trucks);

void print_summary(const std::vector<Truck>& trucks, const Plan& plan);