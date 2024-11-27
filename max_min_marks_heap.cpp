#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "Enter the number of students: ";
    cin >> n;

    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;

    cout << "Enter the marks of students: ";

    for (int i = 0; i < n; ++i) {
        int mark;
        cin >> mark;
        maxHeap.push(mark);
        minHeap.push(mark);
    }

    int maxMarks = maxHeap.top();
    int minMarks = minHeap.top();

    cout << "Maximum marks obtained: " << maxMarks << endl;
    cout << "Minimum marks obtained: " << minMarks << endl;

    return 0;
}
