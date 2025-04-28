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
                cout << "-x_" << (int)A[i][j] * -1 << "\t";
            } 
            else if (j == 0 && i > 0) {
                if (A[i][j] > 0) {
                    cout << "y_" << (int)A[i][j] << "\t";
                } 
                else if (A[i][j] < 0) {
                    cout << "x_" << (int)A[i][j] * -1 << "\t";
                } 
                else {
                    cout << A[i][j] << "\t";
                }
            } 
            else {
                cout << A[i][j] << "\t";
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

void init(vector<vector<float>>& A, vector<vector<float>>& x, const string& filename, int& n, int& m) {  
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file." << "\n";
        return;
    }
    
    file >> n >> m; 

    x.assign(n, vector<float>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {  
            file >> x[i][j];
        }
    }
    A.assign(n -1, vector<float>(m - 1));

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < m - 1; ++j) {  
            A[i][j] = x[i + 1][j + 1];
        }
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            x[i][j] = 0;
        }
    }
    n--;
    m--;
    file.close();
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
void wrapper(vector<vector<float>>& A, vector<vector<float>>& x){
    int r,s,n,m;
    vector <vector<float>> buffer;
    init(A, x, "test.txt", n, m);


    cout << "Eh matrix:\n";
    buffer = x;
    copy_matrix_to_x(A, buffer);
    eliminate_columns(buffer);
    printMatrix(buffer);

    prep(A,x);

    cout << "Eh simplex matrix:\n";
    buffer = x;
    copy_matrix_to_x(A, buffer);
    eliminate_columns(buffer);
    printMatrix(buffer);

    
    int bagana, mur, counter = 1;
    
    while (true){
        
        // printMatrix(x);
        // cout << "\n";
        bagana = bagana_songoh(A);
    
        if (bagana == -1) {
            cout << "sul gishuud bugd surug bish\ntulguur shiid :\n";
            //printMatrix(x);
            for (int i = 0; i < n - 1; i++) {
                if (x[i + 1][0] < 0){
                    cout << "x_" << (int)(-1 * x[i + 1][0]) << " = " << A[i][A[0].size() - 1]; 
                    for(int j = 0; j < m - 1; j++){
                        if(x[0][j + 1] < 0 && x[i + 1][0] < 0){
                            cout << " + " << "(" << -1 * A[i][j] << ") * " << "x_" << (int)(-1 * x[0][j + 1]);
                        }
                    }
                    cout << "\n";
                }
            }
            for (int i = 0; i < m - 1; i++){
                if(x[0][i + 1] < 0){
                    for(int j = 0; j < n -1; j++){
                        cout << "x_" << (int)(-1 * x[0][i + 1]) << " = " << 0 << "\n";
                        break;
                    }
                }
            }
            cout << "Hyzgaariin function-ii utga : " << A[A.size() - 1][A[0].size() - 1] << "\n";
            return;
        }
        mur = mur_songoh(A, bagana);
        if(mur == -1 || bagana == -2){
            cout << "niitsgui\n";
            return;
        }

        if(A[mur][bagana] != 0)
            transformer(A, x, mur, bagana);
        cout << "huvirgalt #" << counter++ << "\n";

        vector < vector <float>> buffer = x;
        copy_matrix_to_x(A, buffer);
        printMatrix(buffer);
        
    }

}
int main() {
    vector<vector<float>> mat, x;
    wrapper(mat,x);
    //printMatrix(x);
    // cout << "\nsystemuud\n";
    // equation(mat,x);

    return 0;
}