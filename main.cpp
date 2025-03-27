#include <iostream>
#include <algorithm>

using namespace std;

const int INF = -1e9;

int maxCoins(int** board, int n) {
    //wyniki będą przechowywane w tablicy trójwymiarowej 2*n*n
    int*** dp = new int**[2];
    for (int i = 0; i < 2; ++i) {
        dp[i] = new int*[n];
        for (int j = 0; j < n; ++j) {
            dp[i][j] = new int[n];
            for (int k = 0; k < n; ++k) {
                dp[i][j][k] = INF;
            }
        }
    }

    //stąd zaczynamy
    dp[0][0][0] = board[0][0];
    //x1:Grażyna, x2:Janusz
    for (int k = 1; k < 2 * (n - 1) + 1; ++k) {
        for (int x1 = max(0, k - n + 1); x1 <= min(n - 1, k); ++x1) {
            for (int x2 = max(0, k - n + 1); x2 <= min(n - 1, k); ++x2) {
                int y1 = k - x1;
                int y2 = k - x2;
                if (y1 >= n || y2 >= n) continue;
                int max_val = INF;


                if (x1 > 0 && x2 > 0)
                    max_val = max(max_val, dp[(k - 1) % 2][x1 - 1][x2 - 1]);
                if (x1 > 0 && y2 > 0)
                    max_val = max(max_val, dp[(k - 1) % 2][x1 - 1][x2]);
                if (y1 > 0 && x2 > 0)
                    max_val = max(max_val, dp[(k - 1) % 2][x1][x2 - 1]);
                if (y1 > 0 && y2 > 0)
                    max_val = max(max_val, dp[(k - 1) % 2][x1][x2]);

                if (max_val == INF) continue;

                dp[k % 2][x1][x2] = max_val + board[x1][y1];
                if (x1 != x2 || y1 != y2) {
                    dp[k % 2][x1][x2] += board[x2][y2];
                }
            }
        }
    }

    int result = dp[(2 * (n - 1)) % 2][n - 1][n - 1];


    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < n; ++j) {
            delete[] dp[i][j];
        }
        delete[] dp[i];
    }
    delete[] dp;

    return result;
}

int main() {
    int n;
    cin >> n;


    int** board = new int*[n];
    for (int i = 0; i < n; ++i) {
        board[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            cin >> board[i][j];
        }
    }

    cout << maxCoins(board, n) << endl;


    for (int i = 0; i < n; ++i) {
        delete[] board[i];
    }
    delete[] board;

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.