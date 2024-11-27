#include <iostream>
#include <list>
#include <vector>
using namespace std;

const int TABLE_SIZE = 10;

struct Client {
    string clientName;
    string clientPhoneNumber;
};

int hashFunction(string clientName, int tableSize) {
    int hash = 0;
    for (char c : clientName) {
        hash += c;
    }
    return hash % tableSize;
}

class HashTableChaining {
private:
    vector<list<pair<string, string>>> hashTable;

public:
    HashTableChaining() {
        hashTable.resize(TABLE_SIZE);
    }

    void insert(string clientName, string clientPhoneNumber) {
        int index = hashFunction(clientName, TABLE_SIZE);
        hashTable[index].push_back(make_pair(clientName, clientPhoneNumber));
    }

    string search(string clientName, int& comparisons) {
        int index = hashFunction(clientName, TABLE_SIZE);
        for (auto &entry : hashTable[index]) {
            comparisons++;
            if (entry.first == clientName) {
                return entry.second;
            }
        }
        return "Not found";
    }
};

class HashTableLinearProbing {
private:
    vector<pair<string, string>> hashTable;
    vector<bool> isSlotOccupied;

public:
    HashTableLinearProbing() {
        hashTable.resize(TABLE_SIZE, {"", ""});
        isSlotOccupied.resize(TABLE_SIZE, false);
    }

    void insert(string clientName, string clientPhoneNumber) {
        int index = hashFunction(clientName, TABLE_SIZE);
        while (isSlotOccupied[index]) {
            index = (index + 1) % TABLE_SIZE;
        }
        hashTable[index] = make_pair(clientName, clientPhoneNumber);
        isSlotOccupied[index] = true;
    }

    string search(string clientName, int& comparisons) {
        int index = hashFunction(clientName, TABLE_SIZE);
        int startIndex = index;

        while (isSlotOccupied[index]) {
            comparisons++;
            if (hashTable[index].first == clientName) {
                return hashTable[index].second;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == startIndex) {
                break;
            }
        }
        return "Not found";
    }
};

void compareCollisionHandling() {
    HashTableChaining chainingTable;
    HashTableLinearProbing probingTable;

    vector<Client> clients = {{"Viraj", "12345"}, {"Atharva", "23456"}, {"sarth", "34567"}, {"Rujuta", "45678"}, {"Janhavi", "56789"}};

    for (const auto& client : clients) {
        chainingTable.insert(client.clientName, client.clientPhoneNumber);
        probingTable.insert(client.clientName, client.clientPhoneNumber);
    }

    vector<string> searchNames = {"Viraj", "Atharva", "sarth", "rujuta", "Pauline", "Unknown"};
    cout << "Comparing Separate Chaining and Linear Probing:\n";

    for (const auto& name : searchNames) {
        int comparisonsChaining = 0, comparisonsProbing = 0;

        string phoneChaining = chainingTable.search(name, comparisonsChaining);
        string phoneProbing = probingTable.search(name, comparisonsProbing);

        cout << "Searching for: " << name << "\n";
        cout << "Separate Chaining - Phone: " << phoneChaining << ", Comparisons: " << comparisonsChaining << "\n";
        cout << "Linear Probing - Phone: " << phoneProbing << ", Comparisons: " << comparisonsProbing << "\n";
        cout << "----------------------\n";
    }
}

int main() {
    compareCollisionHandling();
    return 0;
}
