#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int>& credits, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = credits[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = credits[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            credits[k] = L[i];
            i++;
        } else {
            credits[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        credits[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        credits[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(vector<int>& credits, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(credits, left, mid);
        mergeSort(credits, mid + 1, right);

        merge(credits, left, mid, right);
    }
}

void printCredits(const vector<int>& credits) {
    for (int credit : credits)
        cout << credit << " ";
    cout << endl;
}

int main() {
    vector<int> credits = {4, 10, 2, 8, 6, 7};
    cout << "Original credits: ";
    printCredits(credits);

    mergeSort(credits, 0, credits.size() - 1);

    cout << "Sorted credits: ";
    printCredits(credits);

    return 0;
}
