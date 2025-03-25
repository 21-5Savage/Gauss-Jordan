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
    x.assign(n + 1, vector <float>(m + 1));
    x[0] = {0, -1, -2, -3, -2};
    x[1][0] = 1;
    x[2][0] = 2;
    x[3][0] = 3;
    x[4][0] = -1;
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

    if (row == -1) {
        return -1;
    }

    for (int j = 0; j < lastColIndex - 1; ++j) {
        if (A[row][j] < 0) {
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
    int bagana, mur, counter = 1;

    while (true){
        bagana = bagana_songoh(A);
    
        if (bagana == -1) {
            cout << "sul gishuud bugd surug bish\ntulguur shiid :\n";
            for (int i = 0; i < n - 1; i++) {
                if (x[i + 1][0] < 0)
                    cout << "x_" << -1 * x[i + 1][0] << " = " << A[i][A[0].size() - 1] << "\n"; 
            }
            for (int i = 0; i < m - 1; i++){
                if(x[0][i + 1] < 0)
                    cout << "x_" << -1 * x[0][i + 1] << " = " << 0 << "\n";
            }
            cout << "Hyzgaariin function-ii utga : " << A[A.size() - 1][A[0].size() - 1] << "\n";
            return;
        }
        mur = mur_songoh(A, bagana);
        if(mur == -1 || bagana == -2){
            cout << "niitsgui\n";
            return;
        }
        if (check(x, mur, bagana)){
            
        }
        transformer(A, x, mur, bagana);
        cout << "#" << counter++ << "\n";
        printMatrix(A);
        //printMatrix(x);
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
