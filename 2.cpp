#include <iostream>
#include <stack>
#include <cctype> // For isdigit()
using namespace std;

// Define a tree node
struct TreeNode {
    char value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char val) : value(val), left(nullptr), right(nullptr) {}
};

// Function to construct the expression tree from postfix
TreeNode* constructExpressionTree(const string& postfix) {
    stack<TreeNode*> st;

    for (char ch : postfix) {
        // If operand, create a node and push onto the stack
        if (isalnum(ch)) {
            st.push(new TreeNode(ch));
        }
        // If operator, pop two nodes, create a new node, and push back onto stack
        else {
            TreeNode* right = st.top(); st.pop();
            TreeNode* left = st.top(); st.pop();
            TreeNode* newNode = new TreeNode(ch);
            newNode->left = left;
            newNode->right = right;
            st.push(newNode);
        }
    }
    // The remaining node in the stack is the root
    return st.top();
}

// Non-recursive inorder traversal
void inorderTraversal(TreeNode* root) {
    stack<TreeNode*> st;
    TreeNode* current = root;

    while (!st.empty() || current) {
        // Reach the leftmost node
        while (current) {
            st.push(current);
            current = current->left;
        }
        // Visit the node
        current = st.top(); st.pop();
        cout << current->value << " ";
        // Visit the right subtree
        current = current->right;
    }
}

int main() {
    string postfix;

    // Taking input from the user
    cout << "Enter a postfix expression: ";
    cin >> postfix;

    // Construct the expression tree
    TreeNode* root = constructExpressionTree(postfix);

    // Perform non-recursive inorder traversal
    cout << "Inorder Traversal of Expression Tree: ";
    inorderTraversal(root);
    cout << endl;

    return 0;
}
//ab+c*d-