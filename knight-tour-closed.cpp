#include <iostream>
#include <iomanip>
using namespace std;

constexpr int N = 8;  // Chessboard size
constexpr int MOVES = N;

const int cx[MOVES] = {1, 1, 2, 2, -1, -1, -2, -2};
const int cy[MOVES] = {2, -2, 1, -1, 2, -2, 1, -1};

bool limits(int x, int y) {
    return x >= 0 && y >= 0 && x < N && y < N;
}

bool isEmpty(const int a[], int x, int y) {
    return (limits(x, y)) && (a[y*N + x]) < 0;
}

int getDegree(const int a[], int x, int y) {
    int count = 0;
    for (int i=0; i<MOVES; ++i)
        if (isEmpty(a, x+cx[i], y+cy[i]))
            count++;

    return count;
}

bool nextMove(int a[], int &x, int &y) {
    int min_deg_idx = -1, min_deg = N+1, nx, ny;

    int start = rand()%MOVES;
    for (int count=0; count<MOVES; ++count) {
        int i = (start+count)%MOVES;
        nx = x + cx[i];
        ny = y + cy[i];

        if (isEmpty(a, nx, ny)) {
            int degree = getDegree(a, nx, ny);
            if (degree < min_deg) {
                min_deg_idx = i;
                min_deg = degree;
            }
        }
    }

    if (min_deg_idx == -1)
        return false;

    nx = x + cx[min_deg_idx];
    ny = y + cy[min_deg_idx];
    a[ny*N + nx] = a[y*N + x] + 1;

    x = nx;
    y = ny;

    return true;
}

void print(const int a[]) {
    cout << "Knight's Tour (Closed Tour):\n";
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            cout << setw(3) << a[i*N + j] << " ";
        }
        cout << "\n";
    }
    // cout << "\n";
}

bool neighbour(int x, int y, int xx, int yy) {
    for (int i=0; i< MOVES; ++i)
        if ((x + cx[i] == xx) && (y + cy[i] == yy))
            return true;

    return false;
}

bool findClosedTour(int m, int n) {
    int a[N*N];
    fill(a, a + N*N, -1);

    int sx = m-1, sy = n-1;
    int x = sx, y = sy;
    a[y*N + x] = 1;

    for (int i=0; i<N*N - 1; ++i)
        if (!nextMove(a, x, y))
            return false;

    if (!neighbour(x, y, sx, sy))
        return false;

    cout << "Attacking square: (" << sx+1 << "," << sy+1 << ")\n";

    print(a);
    return true;
}

int main() {
    int a, b;
    cout << "Starting position: ";
    cin >> a >> b ;

    while (!findClosedTour(a,b));
    // int maxAttempts = 1000, attempts = 0;
    // while (!findClosedTour(a,b) && attempts++ < maxAttempts);

    // if (attempts == maxAttempts)
    //     cout << "No solution found after " << maxAttempts << " attempts.\n";

    return 0;
}
