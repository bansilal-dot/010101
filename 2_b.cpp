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
        while (current) {
            st.push(current);
            current = current->left;
        }
        current = st.top(); st.pop();
        cout << current->value << " ";
        current = current->right;
    }
}

// Non-recursive pre-order traversal
void preorderTraversal(TreeNode* root) {
    if (!root) return;

    stack<TreeNode*> st;
    st.push(root);

    while (!st.empty()) {
        TreeNode* node = st.top(); st.pop();
        cout << node->value << " ";

        // Push right child first, then left child
        if (node->right) st.push(node->right);
        if (node->left) st.push(node->left);
    }
}

// Non-recursive post-order traversal
void postorderTraversal(TreeNode* root) {
    if (!root) return;

    stack<TreeNode*> st1, st2;
    st1.push(root);

    while (!st1.empty()) {
        TreeNode* node = st1.top(); st1.pop();
        st2.push(node);

        if (node->left) st1.push(node->left);
        if (node->right) st1.push(node->right);
    }

    while (!st2.empty()) {
        cout << st2.top()->value << " ";
        st2.pop();
    }
}

int main() {
    string postfix;

    // Taking input from the user
    cout << "Enter a postfix expression: ";
    cin >> postfix;

    // Construct the expression tree
    TreeNode* root = constructExpressionTree(postfix);

    // Perform non-recursive traversals
    cout << "Non-recursive Inorder Traversal: ";
    inorderTraversal(root);
    cout << endl;

    cout << "Non-recursive Preorder Traversal: ";
    preorderTraversal(root);
    cout << endl;

    cout << "Non-recursive Postorder Traversal: ";
    postorderTraversal(root);
    cout << endl;

    return 0;
}
//ab+c*d-