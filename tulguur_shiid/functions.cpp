#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <cfloat>
#include <sstream>
#include <iomanip>
using namespace std;

void printMatrix(const vector<vector<float>>& A) {
    int rows = A.size();
    int cols = rows ? A[0].size() : 0;


    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i == 0 && j > 0 && A[i][j] != 0) {
                if(A[i][j] > 0){
                    cout << "y_" << (int)A[i][j] << "\t";
                }
                else{
                    cout << "-x_" << (int)A[i][j] * -1 << "\t";
                }
                
            } 
            else if (j == 0 && i > 0) {
                if (A[i][j] > 0) {
                    cout << "y_" << (int)A[i][j] << "\t";
                } 
                else if (A[i][j] < 0) {
                    cout << "x_" << (int)A[i][j] * -1 << "\t";
                } 
                else {
                    cout << fixed << setprecision(2) << A[i][j] << "\t";
                }
            } 
            else {
                cout << fixed << setprecision(2) << A[i][j] << "\t";
            }
        }
        cout << "\n";

    }
    cout << "\n";
}

void equation(const vector<vector<float>>& A, const vector<vector<float>>& x) {
    for (int i = 1; i < x.size(); i++) {
        float sum = 0;
        cout << "";
        for (int j = 1; j < x[i].size(); j++) {
            if (x[i][j] == 1 || x[i][j] == 2) {
                float value = x[0][j] * A[i - 1][j - 1];
                sum += value;
                cout << value;
                if (j < x[i].size() - 1) cout << " + ";
            }
        }
        cout << " = x" << i << "\t\tx" << i << " = " << sum << "\n";
    }
}

void transformer(vector<vector<float>>& A, vector<vector<float>>& x, int r, int s) {
    int n = A.size();
    if (n == 0 || A[0].empty()) return;
    int m = A[0].size();

    if (A[r][s] == 0) {
        cout << "div by 0\n";
        return;
    }

    float pivot = 1.0 / A[r][s];
    cout << "\nPivot: " << A[r][s] << "  [" << r << "][" << s << "], Urvuu: " << pivot << "\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i != r && j != s) {
                A[i][j] = (A[i][j] * A[r][s] - A[i][s] * A[r][j]) * pivot;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == r) 
                A[i][j] *= pivot;
            if (j == s) 
                A[i][j] *= -pivot;
        }
    }

    A[r][s] = pivot;

    for (int j = 1; j <= m; j++) {
        x[r + 1][j] = 1;
    }

    for (int i = 1; i <= n; i++) {
        x[i][s + 1] = 1;
    }
    x[r + 1][s + 1] = 2;
    swap(x[r + 1][0],x[0][s + 1]);
}

bool check(vector<vector<float>>& x, int r, int s){
    int n = x.size();
    int m = x[0].size();
    if(x[r + 1][s + 1] == 0){
        return true;
    }
    for(int k = 1; k < n; k++){
        if(x[k][s + 1] > 0){
            return false;
        }
    }
    
    return false;
}

void copy_matrix_to_x(vector<vector<float>>& A, vector<vector<float>>& x) {
    int n = A.size();     // Number of rows in A
    int m = A[0].size();  // Number of columns in A

    // Ensure x is of size (n+1) x (m+1)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // Copy elements from A into x starting at x[1][1]
            x[i+1][j+1] = A[i][j];
        }
    }
}

void eliminate_columns(std::vector<std::vector<float>>& x) {
    int rows = x.size();
    int cols = x[0].size();

    std::vector<int> columns_to_remove;
    for (int j = 1; j < cols - 1; ++j) { 
        if (x[0][j] == 0) {
            columns_to_remove.push_back(j);
        }
    }

    if (columns_to_remove.empty()) return;

    std::vector<std::vector<float>> new_x(rows, std::vector<float>(cols - columns_to_remove.size()));

    for (int i = 0; i < rows; ++i) {
        int new_col_index = 0;
        for (int j = 0; j < cols; ++j) {
            if (std::find(columns_to_remove.begin(), columns_to_remove.end(), j) == columns_to_remove.end() || j == cols - 1) {
                new_x[i][new_col_index++] = x[i][j];
            }
        }
    }

    x = new_x;
}

int bagana_songoh(vector<vector<float>>& A) {
    int n = A.size();
    if (n == 0 || A[0].empty())
        return -1; 

    int m = A[0].size();
    int lastColIndex = m - 1;
    int row = -1;

    for (int i = 0; i < n - 1; ++i) {
        if (A[i][lastColIndex] < 0 || A[i][lastColIndex] == 0) {
            row = i;
            break;
        }
    }

    if (row == -1) {
        return -1;
    }

    for (int j = 0; j < lastColIndex - 1; ++j) {
        if (A[row][j] < 0 || A[row][j] == 0) {
            return j; 
        }
    }
    return -2;
}

int mur_songoh(vector<vector<float>>& A, int bagana) {
    int n = A.size();
    if (n == 0 || A[0].empty())
        return -1; 

    int m = A[0].size();
    int lastColIndex = m - 1;
    int selectedRow = -1;
    float minRatio = FLT_MAX; 

    for (int i = 0; i < n - 1; ++i) {
        if (A[i][bagana] > 0 && A[i][lastColIndex] > 0) {
            float ratio = A[i][lastColIndex] / A[i][bagana];
            if (ratio < minRatio) {
                minRatio = ratio;
                selectedRow = i;
            }
        }
    }

    return selectedRow; 
}

void prep(vector<vector<float>> &A, vector<vector<float>> &x){
    int n = A.size();
    int m = A[0].size();
    vector <vector<float>> buffer;
    for(int i = 0; i < n; i++){
        if(x[i + 1][0] == 0){
            //cout << "zero detected fixing [" << i+1 << "]\n"; 
            for(int j = 0; j < m; j++){
                if(x[0][j + 1] < 0){
                    //cout << "pivot ["<< i <<"]["<< j <<"]\n";
                    
                    if(A[i][j] != 0)
                        transformer(A, x, i, j);
                    buffer = x;
                    copy_matrix_to_x(A, buffer);
                    // printMatrix(buffer);
                    break;
                }
            }
        }
    }
    cout << "Simplex huvirgalt duussan\n";
}

int simplex_ratio(const vector<vector<float>>& A, int bagana) {
    int min_row = -1;
    float min_ratio = numeric_limits<float>::max();
    int num_rows = A.size();
    int last_col = A[0].size() - 1;

    for (int i = 1; i < num_rows - 1; ++i) {
        float denominator = A[i][bagana];
        float constant = A[i][last_col];

        if (denominator > 0) {
            float ratio = constant / denominator;
            if (ratio < min_ratio) {
                min_ratio = ratio;
                min_row = i;
            }
        }
    }

    return min_row;
}


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

