#include<bits/stdc++.h>
using namespace std;

int n;
int sroot;

bool solve(int i, int j, vector<vector<char>>&board, int rows[], int column[], vector<vector<int>>&subgrid) {
    if (i >= n || j >= n) {
        return true;
    }
    if (board[i][j] == '0') {
        for (int k = 1; k <= n; k++) {
            int mask = 1 << (k - 1);
            if (!(rows[i]&mask || column[j]&mask || subgrid[i / sroot][j / sroot]&mask)) {
                rows[i] |= mask;
                column[j] |= mask;
                board[i][j] = k + '0';
                //cout << board[i][j] << endl;
                subgrid[i / sroot][j / sroot] |= mask;
                bool issolved = false;
                if (j == 8) {
                    issolved = solve(i + 1, 0, board, rows, column, subgrid);
                }
                else {
                    issolved = solve(i, j + 1, board, rows, column, subgrid);
                }
                if (issolved) {
                    return true;
                }
                else {
                    rows[i] &= (~mask);
                    column[j] &= (~mask);
                    subgrid[i / sroot][j / sroot] &= (~mask);
                    board[i][j] = '0';
                }
            }
        }
        return false;
    }
    if (j == 8) {
        return solve(i + 1, 0, board, rows, column, subgrid);
    }
    else {
        return solve(i, j + 1, board, rows, column, subgrid);
    }
}
void c_p_c() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}
int main() {
    c_p_c();
    cin >> n;

    vector<vector<char>>board(n);
    for (int i = 0; i < n; i++) {
        board[i].resize(n, '0');
    }

    int rows[n];
    int column[n];
    fill(rows, rows + n, 0);
    fill(column, column + n, 0);
    vector<vector<int>>subgrid(n);
    for (int i = 0; i < n; i++) {
        subgrid[i].resize(n, 0);
    }

    sroot = sqrt(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
            int mask = 1 << (board[i][j] - '1');
            rows[i] |= mask;
            column[j] |= mask;
            subgrid[i / sroot][j / sroot] |= mask;
        }
    }

    bool issolved = solve(0, 0, board, rows, column, subgrid);

    if (issolved) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << board[i][j];
            }
            cout << endl;
        }
    }
    else {
        cout << "Invalid Grid\n";
    }
    return 0;
}








