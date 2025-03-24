#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <cfloat>
#include <sstream>
using namespace std;

void printMatrix(const vector<vector<float>>& A) {
    for (const auto &row : A) {
        for (float val : row) {  
            cout << val << " ";
        }
        cout << '\n';
    }
}

void init(vector<vector<float>>& A, vector<vector<float>>& x, const string& filename, int& n, int& m) {  
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file." << "\n";
        return;
    }
    
    file >> n >> m; 

    A.assign(n, vector<float>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {  
            file >> A[i][j];
        }
    }

    file.close();
}




void transformer(vector<vector<float>>& A, int r, int s) {
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
}

bool check(vector<vector<float>>& x, int r, int s){
    for(int k = 1; k <= 3; k++){
        if(x[k][s + 1] == 2){
            return false;
        }
    }
    if(x[r + 1][s + 1] == 0){
        return true;
    }
    return false;
}

int bagana_songoh(vector<vector<float>>& A) {
    int n = A.size();
    if (n == 0 || A[0].empty())
        return -1; 

    int m = A[0].size();
    int lastColIndex = m - 1;
    int row = -1;

    for (int i = 0; i < n - 1; ++i) {
        if (A[i][lastColIndex] < 0) {
            row = i;
            break;
        }
    }

    if (row == -1) 
        return -1;

    for (int j = 0; j < m; ++j) {
        if (A[row][j] < 0) {
            return j; 
        }
    }

    return -1;
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
        float ratio = A[i][lastColIndex] / A[i][bagana];
            if (ratio < minRatio && ratio > 0) {
                
                minRatio = ratio;
                selectedRow = i;
            }
    }

    return selectedRow; 
}

void wrapper(vector<vector<float>>& A, vector<vector<float>>& x){
    int r,s,n,m;
    init(A, x, "B.txt", n, m);
    cout << "Eh matrix:\n";
    printMatrix(A);
    int bagana, mur;

    while (bagana != -1 || mur != -1){
        bagana = bagana_songoh(A);
    
        if(bagana == -1){
            cout << "sul gishuud bugd surug bish\n";
            return;
        }
        mur = mur_songoh(A, bagana);
        if(mur == -1){
            cout << "niitsgui\n";
            return;
        }

        transformer(A, mur, bagana);

        printMatrix(A);
    }

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
int main() {
    vector<vector<float>> mat, x;
    wrapper(mat,x);
    // cout << "\nsystemuud\n";
    // equation(mat,x);

    return 0;
}
