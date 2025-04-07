#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

void slice_matrix(const vector<vector<float>>& A, vector<vector<float>>& B) {
    int n = A.size();        // total rows
    int m = A[0].size();     // total columns

    // Resize B to (n - 1) rows and (m - 1) columns
    B.resize(n - 1);

    for (int i = 1; i < n; ++i) {
        B[i - 1].resize(m - 1);  // Resize each row of B
        for (int j = 1; j < m; ++j) {
            B[i - 1][j - 1] = A[i][j];  // Copy elements excluding the first column and row
        }
    }
}

int main() {
    vector<vector<float>> A = {
        {1, 1, 1, 1, 1},
        {1, 1.50, -0.50, 1.00, 3.00},
        {1, -0.50, 1.50, 0.00, 2.00},
        {1, 5.00, 6.00, 3.00, 4.00},
        {1, 0.00, 4.00, 4.00, 3.00}
    };

    vector<vector<float>> B;

    slice_matrix(A, B);

    // Print matrix B after slicing
    for (const auto& row : B) {
        for (float val : row) {
            cout << fixed << setprecision(2) << val << " ";
        }
        cout << endl;
    }

    return 0;
}