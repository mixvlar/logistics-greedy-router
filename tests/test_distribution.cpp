#include <gtest/gtest.h>
#include "../src/distribution/distribution.h"
#include "../include/types.h"

using namespace std;

TEST(DistributionBasic, AllOrdersFitOneTruck) {
    vector<Order> orders = {Order{1, 5.0, "north"}, Order{2, 5.0, "north"}};
    vector<Truck> trucks = {Truck{101, 20.0, 0.0, "north"}};

    Plan plan = build_plan_greedy(orders, trucks);

    EXPECT_EQ(plan.assignments.size(), 2);
    EXPECT_TRUE(plan.unassigned_orders.empty());
}

TEST(DistributionBasic, OrderHeavierThanAnyTruck) {
    vector<Order> orders = {Order{1, 50.0, "north"}};
    vector<Truck> trucks = {Truck{101, 20.0, 0.0, "north"}};

    Plan plan = build_plan_greedy(orders, trucks);

    EXPECT_TRUE(plan.assignments.empty());
    EXPECT_EQ(plan.unassigned_orders.size(), 1);
}

TEST(DistributionBasic, SomeOrdersUnassigned) {
    vector<Order> orders = {Order{1, 10.0, "south"}, Order{2, 10.0, "south"}, Order{3, 10.0, "south"}};
    vector<Truck> trucks = {Truck{101, 15.0, 0.0, "south"}, Truck{102, 10.0, 0.0, "south"}};

    Plan plan = build_plan_greedy(orders, trucks);

    EXPECT_EQ(plan.unassigned_orders.size(), 1);
}

TEST(DistributionBasic, OrderWeightExactlyFits) {
    vector<Order> orders = {Order{1, 15.0, "east"}};
    vector<Truck> trucks = {Truck{101, 15.0, 0.0, "east"}};

    Plan plan = build_plan_greedy(orders, trucks);

    EXPECT_EQ(plan.assignments.size(), 1);
    EXPECT_TRUE(plan.unassigned_orders.empty());
}

TEST(DistributionBasic, EmptyOrders) {
    vector<Order> orders = {};
    vector<Truck> trucks = {Truck{101, 20.0, 0.0, "west"}};

    Plan plan = build_plan_greedy(orders, trucks);

    EXPECT_TRUE(plan.assignments.empty());
    EXPECT_TRUE(plan.unassigned_orders.empty());
}