#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Job {
    char id;        // Job ID
    int deadline;   // Deadline for the job
    int profit;     // Profit for the job
};

bool compare(Job a, Job b) {
    return a.profit > b.profit; // Sort jobs by profit in descending order
}

void jobScheduling(vector<Job> &jobs, int n) {
    sort(jobs.begin(), jobs.end(), compare); // Sort jobs by profit

    vector<int> result(n, -1); // To store the job sequence (-1 indicates empty)
    vector<bool> slot(n, false); // To mark if a slot is filled

    int maxProfit = 0;

    for (int i = 0; i < jobs.size(); i++) {
        for (int j = min(jobs[i].deadline - 1, n - 1); j >= 0; j--) {
            if (!slot[j]) { // If the slot is free
                result[j] = i;
                slot[j] = true;
                maxProfit += jobs[i].profit;
                break;
            }
        }
    }

    cout << "Selected jobs and their deadlines:\n";
    for (int i = 0; i < n; i++) {
        if (result[i] != -1) {
            cout << "Job " << jobs[result[i]].id 
                 << " with Deadline " << jobs[result[i]].deadline 
                 << " and Profit " << jobs[result[i]].profit << endl;
        }
    }

    cout << "Maximum Profit: " << maxProfit << endl;
}

int main() {
    int n = 5; // Number of jobs
    vector<Job> jobs = {
        {'A', 2, 100},
        {'B', 1, 19},
        {'C', 2, 27},
        {'D', 1, 25},
        {'E', 3, 15}
    };

    cout << "Enter the maximum number of time slots: ";
    int timeSlots;
    cin >> timeSlots;

    jobScheduling(jobs, timeSlots);

    return 0;
}
