#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }

    return root;
}

void display(Node* root) {
    if (root == nullptr) {
        return;
    }
    display(root->left);
    cout << root->data << " ";
    display(root->right);
}

// Function to find the depth of the binary tree
int findDepth(Node* root) {
    if (root == nullptr) {
        return 0;
    }

    int leftDepth = findDepth(root->left);
    int rightDepth = findDepth(root->right);

    return max(leftDepth, rightDepth) + 1;
}

void displayLeafNodes(Node* root) {
    if (root == nullptr) {
        return;
    }

    if (root->left == nullptr && root->right == nullptr) {
        cout << root->data << " ";
        return;
    }

    displayLeafNodes(root->left);
    displayLeafNodes(root->right);
}

Node* copyTree(Node* root) {
    if (root == nullptr) {
        return nullptr;
    }

    Node* newNode = new Node(root->data);
    newNode->left = copyTree(root->left);
    newNode->right = copyTree(root->right);

    return newNode;
}

int main() {
    Node* root = nullptr;

    int choice, value;
    do {
        cout << "\nBinary Tree Operations Menu:";
        cout << "\n1. Insert";
        cout << "\n2. Display (In-order Traversal)";
        cout << "\n3. Find Depth of Tree";
        cout << "\n4. Display Leaf Nodes";
        cout << "\n5. Create a Copy of Tree";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                root = insert(root, value);
                break;

            case 2:
                cout << "Binary Tree (In-order): ";
                display(root);
                cout << endl;
                break;

            case 3:
                cout << "Depth of the Tree: " << findDepth(root) << endl;
                break;

            case 4:
                cout << "Leaf Nodes: ";
                displayLeafNodes(root);
                cout << endl;
                break;

            case 5: {
                Node* copiedTree = copyTree(root);
                cout << "Copied Tree (In-order): ";
                display(copiedTree);
                cout << endl;
                break;
            }

            case 6:
                cout << "Exiting program..." << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
