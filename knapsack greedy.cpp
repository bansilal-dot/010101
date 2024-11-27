#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    double weight;
    double value;

    Item(double w, double v) : weight(w), value(v) {}
};

bool compare(Item a, Item b) {
    return (a.value / a.weight) > (b.value / b.weight);
}

double fractionalKnapsack(vector<Item> &items, double capacity) {
    sort(items.begin(), items.end(), compare); 
    double totalValue = 0.0;

    for (auto &item : items) {
        if (capacity >= item.weight) {
            capacity -= item.weight;
            totalValue += item.value;
        } else {
            totalValue += item.value * (capacity / item.weight); 
            break; 
        }
    }

    return totalValue;
}

int main() {
    int n;
    double capacity;

    cout << "Enter the number of items: ";
    cin >> n;

    vector<Item> items;

    for (int i = 0; i < n; i++) {
        double weight, value;
        cout << "Enter weight and value of item " << i + 1 << ": ";
        cin >> weight >> value;
        items.emplace_back(weight, value);
    }

    cout << "Enter the knapsack capacity: ";
    cin >> capacity;

    double maxValue = fractionalKnapsack(items, capacity);
    cout << "Maximum total value in the knapsack: " << maxValue << endl;

    return 0;
}
