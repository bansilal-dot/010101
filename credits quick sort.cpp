#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Student {
    string name;
    int credits;
};

int partition(vector<Student> &students, int low, int high) {
    int pivot = students[high].credits;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (students[j].credits > pivot) { // Sorting in descending order
            i++;
            swap(students[i], students[j]);
        }
    }
    swap(students[i + 1], students[high]);
    return i + 1;
}

void quickSort(vector<Student> &students, int low, int high) {
    if (low < high) {
        int pi = partition(students, low, high);
        quickSort(students, low, pi - 1);
        quickSort(students, pi + 1, high);
    }
}

int main() {
    int n;
    cout << "Enter the number of students: ";
    cin >> n;

    vector<Student> students(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter the name of student " << i + 1 << ": ";
        cin >> students[i].name;
        cout << "Enter the credits received by " << students[i].name << " in the last 2 years: ";
        cin >> students[i].credits;
    }

    quickSort(students, 0, n - 1);

    cout << "Top 3 students based on credits:" << endl;
    for (int i = 0; i < min(3, n); i++) {
        cout << students[i].name << " with " << students[i].credits << " credits" << endl;
    }

    return 0;
}
