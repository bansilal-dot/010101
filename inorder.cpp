#include <iostream>
#include <stack>
#include <cctype> 
using namespace std;

struct TreeNode {
    char value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char val) : value(val), left(nullptr), right(nullptr) {}
};

TreeNode* constructExpressionTree(const string& postfix) {
    stack<TreeNode*> st;

    for (char ch : postfix) {
        if (isalnum(ch)) {
            st.push(new TreeNode(ch));
        }
      
        else {
            TreeNode* right = st.top(); st.pop();
            TreeNode* left = st.top(); st.pop();
            TreeNode* newNode = new TreeNode(ch);
            newNode->left = left;
            newNode->right = right;
            st.push(newNode);
        }
    }

    return st.top();
}
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

int main() {
    string postfix;

    cout << "Enter a postfix expression: ";
    cin >> postfix;

    TreeNode* root = constructExpressionTree(postfix);


    cout << "Inorder Traversal of Expression Tree: ";
    inorderTraversal(root);
    cout << endl;

    return 0;
}
//ab+c*d-
