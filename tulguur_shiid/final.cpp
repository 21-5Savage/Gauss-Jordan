#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <cfloat>
#include <sstream>
#include <iomanip>
#include "functions.cpp"
using namespace std;

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

vector<vector<float>> wrapper(vector<vector<float>>& A, vector<vector<float>>& x){
    int r,s,n,m;
    vector <vector<float>> buffer;
    init(A, x, "t1.txt", n, m);


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
            slice_matrix(buffer, A);
            return buffer;
        }
        mur = mur_songoh(A, bagana);
        if(mur == -1 || bagana == -2){
            cout << "niitsgui\n";
            slice_matrix(buffer, A);
            return buffer;
        }

        if(A[mur][bagana] != 0)
            transformer(A, x, mur, bagana);
        cout << "huvirgalt #" << counter++ << "\n";

        vector < vector <float>> buffer = x;
        copy_matrix_to_x(A, buffer);
        printMatrix(buffer);
        
    }
    slice_matrix(buffer, A);
    return buffer;
}

int maximize(const vector<vector<float>>& A, int& bagana, int& mur) {
    int n = A.size();
    int m = A[0].size();
    bagana = -1;
    mur = -1;
    int optimal_found = 1, niitsgui = 1;

    for (int i = 1; i < m - 1; i++) {
        if (A[n - 1][i] < 0) {
            optimal_found = 0;
            int temp_mur = simplex_ratio(A, i);

            if (temp_mur != -1) {
                bagana = i;
                mur = temp_mur;
                niitsgui = 0;
                return 1; 
            }
        }
    }
    if(optimal_found)
        cout << "Onovchtoi shiid oldson\n";
    if(niitsgui && !optimal_found)
        cout << "Niitsgui\n";
    return 0;  
}

int minimize(const vector<vector<float>>& A, int& bagana, int& mur) {
    int n = A.size();
    int m = A[0].size();
    bagana = -1;
    mur = -1;
    int optimal_found = 1, niitsgui = 1;
    for (int i = 1; i < m - 1; i++) {
        if (A[n - 1][i] > 0) {
            optimal_found = 0;
            int temp_mur = simplex_ratio(A, i);

            if (temp_mur != -1) {
                bagana = i;
                mur = temp_mur;
                niitsgui = 0;
                return 1;  
            }
        }
    }

    if(optimal_found)
        cout << "Onovchtoi shiid oldson\n";
    if(niitsgui && !optimal_found)
        cout << "Niitsgui\n";
    return 0; 
}


void final(vector<vector<float>>& A, vector<vector<float>>& x){
    vector<vector<float>> B = x;
    copy_matrix_to_x(A,B);
    int n = B.size();
    int m = B[0].size();
    int max = 0;
    int bagana, mur;
    
    cout << "Max : 1, Min : 0\n";
    cin >> max;
    if(max == 1){
        while(maximize(B, bagana, mur) == 1){
            cout << "bagana : "<< bagana << "\nmur : " << mur <<"\n";
            cout << "pivot : " << B[mur][bagana] << "\n";
            slice_matrix(B, A);
            transformer(A,x, mur - 1, bagana - 1);
            B = x;
            copy_matrix_to_x(A,B);
            printMatrix(B);
        }
    }
    else{
        while(minimize(B, bagana, mur) == 1){
            cout << "bagana : "<< bagana << "\nmur : " << mur <<"\n";
            cout << "pivot : " << B[mur][bagana] << "\n";
            slice_matrix(B, A);
            transformer(A,x, mur - 1, bagana - 1);
            B = x;
            copy_matrix_to_x(A,B);
            printMatrix(B);
        }
    }
    cout << "\n";
    //printMatrix(A);
}

int main() {
    vector<vector<float>> A, x, buffer;
    buffer = wrapper(A,x);
    eliminate_columns(x);
    final(A,x);
    //printMatrix(x);
    // cout << "\nsystemuud\n";
    // equation(mat,x);

    return 0;
}