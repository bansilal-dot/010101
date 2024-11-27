#include <iostream>
#include <vector>
using namespace std;

bool isSafe(vector<vector<int>> &board, int row, int col, int n) {
    for (int i = 0; i < row; i++)
        if (board[i][col])
            return false;

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    for (int i = row, j = col; i >= 0 && j < n; i--, j++)
        if (board[i][j])
            return false;

    return true;
}

bool solveNQUtil(vector<vector<int>> &board, int row, int n) {
    if (row >= n)
        return true;

    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col, n)) {
            board[row][col] = 1;
            if (solveNQUtil(board, row + 1, n))
                return true;
            board[row][col] = 0;
        }
    }

    return false;
}

void solveNQ(int n) {
    vector<vector<int>> board(n, vector<int>(n, 0));
    if (solveNQUtil(board, 0, n)) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << board[i][j] << " ";
            cout << endl;
        }
    } else {
        cout << "Solution does not exist" << endl;
    }
}

int main() {
    int n;
    cout << "Enter the size of the board: ";
    cin >> n;
    solveNQ(n);
    return 0;
}
