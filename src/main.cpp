#include <iostream>
#include <vector>
#include <string>
#include "../include/types.h"
#include "distribution/distribution.h"
#include "file_io/file_io.h"

using namespace std;


int main() {

    string orders_file;
    string trucks_file;
    string report_file;


    cout<<"Enter orders file name: ";
    cin >> orders_file;
    cout<<"Enter trucks file name: ";
    cin >> trucks_file;
    cout<<"Enter result file name: ";
    cin >> report_file;
    

    vector<Order> orders;
    vector<Truck> trucks;

    cout << "Start..." << endl;

    if (!load_orders(orders_file, orders))
        return 1;
    if (!load_trucks(trucks_file, trucks))
        return 1;
    
    cout << "Successfully loaded " << orders.size() << " orders and " 
         << trucks.size() << " trucks." << endl;

    cout << "Running greedy distribution algorithm..." << endl;
    Plan plan = build_plan_greedy(orders, trucks);

    print_summary(trucks, plan);

    if (!save_report(report_file, plan, trucks))
        return 1;
    
    cout << "Done! Check " << report_file << endl;
    return 0;
}