#include "file_io.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void trim_cr(string& s){
    if (!s.empty() && s.back()== '\r')
        s.pop_back();
}

bool load_orders(const string& filename, vector<Order>& orders){
    ifstream file(filename);
    if (!file.is_open()){
        cout<<"Failed to load orders! Can't open: "<<filename<<endl;
        return false;
    }

    string line;
    while (getline(file, line)){
        trim_cr(line);
        if (line.empty()) continue;

        stringstream ss(line);
        string id_str, zone, weight_str;

        while (getline(ss,id_str, ',') &&  getline(ss,zone,',') && getline(ss,weight_str, ',')) {
            Order order;
            order.id = stoi(id_str);
            order.zone = zone;
            order.weight = stod(weight_str);
            orders.push_back(order);
        }
    }

    file.close();
    return true;
}



bool load_trucks(const string& filename, vector<Truck>& trucks) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout<<"Failed to load trucks! Can't open: "<<filename<<endl;
        return false;
    }

    string line;

    while (getline(file, line)) {
        trim_cr(line);
        if (line.empty()) continue;

        stringstream ss(line);
        string id_str, capacity_str, zone;

        if (getline(ss, id_str, ',') && getline(ss, capacity_str, ',') && getline(ss, zone, ',')) {
            Truck truck;
            truck.id = stoi(id_str);
            truck.max_capacity = stod(capacity_str);
            truck.zone = zone;
            truck.current_weight = 0.0;
            string base_point;
            if (getline(ss, base_point, ','))
                truck.base_point = base_point;
            trucks.push_back(truck);
        }
    }

    file.close();
    return true;
}

bool save_report(const string& filename, const Plan& plan, const vector<Truck>& trucks) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout<<"Failed to save a report! Can't open: "<<filename<<endl;
        return false;
    }

    file << "<Trucks' loading report>\n\n";

    for (const auto& truck : trucks) {
        file << "Truck's id: " << truck.id << " | Zone: " << truck.zone;
        if (!truck.base_point.empty())
            file << "| Base point: " << truck.base_point;

        file << " | Weight: " << truck.current_weight << "/" << truck.max_capacity << endl;

        file << " Order's list: ";
        bool first = true;
        for (const auto& ask : plan.assignments) {
            if (ask.truck_id == truck.id) {
                if (!first)
                    file << ", ";
                file << ask.order_id;
                first = false;
            }
        }
        if (first)
            file << "(No orders for this truck!)";
        file << "\n----------------------------------------------------------\n";
    }

    file << "\n Unassigned orders:\n";
    if (plan.unassigned_orders.empty())
        file << "All orders are distributed!" << endl;
    else
        for (const auto& order : plan.unassigned_orders)
            file << "Order's id: " << order.id << " | Zone: " << order.zone << " | Weight: " << order.weight << endl;

    file.close();
    return true;
}


void print_summary(const vector<Truck>& trucks, const Plan& plan) {
    cout << "\n==========================================" << endl;
    cout << "         SHORT DISTRIBUTION SUMMARY       " << endl;
    cout << "==========================================" << endl;
    cout << " Total trucks available: " << trucks.size() << endl;
    cout << " Assigned orders:        " << plan.assignments.size() << endl;
    cout << " Unassigned orders:      " << plan.unassigned_orders.size() << endl;
    cout << "==========================================\n" << endl;
}