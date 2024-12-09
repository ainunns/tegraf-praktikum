#include <iostream>
#include <vector>

using namespace std;

// Function to check if a move is valid
bool isValidMove(int x, int y, int N, vector<vector<int>> &board) {
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
}

// Function to find the next possible move for the knight
vector<pair<int, int>> getPossibleMoves(int x, int y, int N, vector<vector<int>> &board) {
    vector<pair<int, int>> moves;
    int dx[] = { -2, -1, 1, 2, 2, 1, -1, -2 };
    int dy[] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    for (int i = 0; i < 8; i++) {
        int nextX = x + dx[i];
        int nextY = y + dy[i];

        if (isValidMove(nextX, nextY, N, board)) {
            moves.push_back({ nextX, nextY });
        }
    }

    return moves;
}

// Function to solve the Knight's Tour problem
bool solveKnightTour(int x, int y, int move, int N, vector<vector< int>> &board) {
    if (move == N * N) {
        return true; // All squares are visited
    }

    vector<pair<int, int>> possibleMoves = getPossibleMoves(x, y, N, board);
    for (auto &nextMove : possibleMoves) {
        int nextX = nextMove.first;
        int nextY = nextMove.second;
        board[nextX][nextY] = move; // Mark the square as visited

        if (solveKnightTour(nextX, nextY, move + 1, N, board)) {
            return true; // Continue to solve
        }

        board[nextX][nextY] = -1; // Backtrack
    }

    return false; // No valid moves
}

// Function to initialize the board and start the tour
void knightTour(int N) {
    vector<vector<int>> board(N, vector<int>(N, -1));
    board[0][0] = 0; // Starting position

    if (solveKnightTour(0, 0, 1, N, board)) {
        // Print the board
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << board[i][j] << "\t";
            }
            cout << endl;
        }
    } else {
        cout << "No solution exists." << endl;
    }
}

int main() {
    int N = 8; // Size of the chessboard
    knightTour(N);
    return 0;
}