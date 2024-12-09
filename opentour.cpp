#include <iostream>
#include <vector>
using namespace std;

const int N = 8; // Ukuran papan catur
int dx[] = {2, 1, -1, -2, -2, -1, 1, 2}; // Gerakan kuda (x)
int dy[] = {1, 2, 2, 1, -1, -2, -2, -1}; // Gerakan kuda (y)

// Fungsi untuk memeriksa apakah langkah valid
bool isSafe(int x, int y, vector<vector<int>>& board) {
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
}

// Fungsi rekursif untuk solusi Open Tour
bool solveOpenTour(int x, int y, int moveCount, vector<vector<int>>& board) {
    if (moveCount == N * N) {
        return true; // Semua kotak telah dikunjungi
    }
    for (int i = 0; i < 8; ++i) {
        int nextX = x + dx[i];
        int nextY = y + dy[i];
        if (isSafe(nextX, nextY, board)) {
            board[nextX][nextY] = moveCount;
            if (solveOpenTour(nextX, nextY, moveCount + 1, board)) {
                return true;
            }
            board[nextX][nextY] = -1; // Backtracking
        }
    }
    return false;
}

// Fungsi utama untuk Open Tour
void openTour() {
    vector<vector<int>> board(N, vector<int>(N, -1));
    int startX = 0, startY = 0; // Posisi awal
    board[startX][startY] = 0; // Langkah pertama

    if (solveOpenTour(startX, startY, 1, board)) {
        for (const auto& row : board) {
            for (int cell : row) {
                cout << cell << "\t";
            }
            cout << endl;
        }
    } else {
        cout << "Solusi tidak ditemukan." << endl;
    }
}

int main() {
    openTour();
    return 0;
}
