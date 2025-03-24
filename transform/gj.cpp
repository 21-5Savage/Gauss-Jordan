#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#define N 3
#define M 4

using namespace std;

void printMatrix(const vector<vector<float>>& A) {
    for (const auto &row : A) {
        for (float val : row) {  
            cout << val << " ";
        }
        cout << '\n';
    }
}

void init(vector<vector<float>>& A, vector<vector<float>>& x, const string& filename) {  
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file." << endl;
        return;
    }
    
    int rows, cols;
    file >> rows >> cols;
    A.resize(rows, vector<float>(cols - 1));
    x.resize(rows + 1, vector<float>(cols, 0));
    
    x[0][0] = -1;
    for (int j = 1; j < cols; ++j) {
        x[0][j] = -1;
    }
    
    for (int i = 0; i < rows; ++i) {
        file >> x[i + 1][0];
        for (int j = 0; j < cols - 1; ++j) {
            file >> A[i][j];
            A[i][j] = -A[i][j];
        }
    }
    file.close();
}

void transformer(vector<vector<float>>& A, int n, int m, int r, int s) {
    if (A[r][s] == 0) {
        cout << "div by 0\n";
        return;
    }
    
    float pivot = 1.0 / A[r][s];
    cout << "\nPivot: " << A[r][s] << "  ["<< r <<"]["<< s <<"]" <<", Urvuu: " << pivot << "\n";


    //busad element
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if(i != r && j != s){
                float old_val = A[i][j];
                //tomyo
                float new_val = (A[i][j] * A[r][s] - A[i][s] * A[r][j]) * pivot;
                //cout << "A[" << i << "][" << j << "] = ("<< old_val << " * " << A[r][s] << " - " << A[i][s] << " * " << A[r][j] << ") * " << pivot << " = " << new_val << "\n";

                A[i][j] = new_val;
            }        
        }
    }
    //gol mur bagana
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if(i == r)
                A[i][j] *= pivot;
            if(j == s)
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

void wrapper(vector<vector<float>>& A, vector<vector<float>>& x){
    int r,s,n,m;
    init(A, x, "A1.txt");
    cout << "Eh matrix:\n";
    printMatrix(A);
    int counter = 1;
    while(true){
        bool exit = false;
       
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                if(check(x, i, j) && A[i][j] != 0){
                    //gol element songoh
                    r = i;
                    s = j;
                    for (int j = 1; j < x[0].size(); j++) {
                        x[r + 1][j] = 1;
                    }
                    x[r + 1][s + 1] = 2;
                    float temp = x[r + 1][0];
                    x[r + 1][0] = x[0][s + 1] * (- 1);
                    x[0][s + 1] = temp * (- 1);
                    
                    transformer(A, 3, 4, r, s); 
                    exit = true;
                    break;
                }
                
            }
            if(exit) 
                break;
        }
        if(exit == false){
            cout << "\nhuvirgalt duussan\n";
            return;
        }
        cout << "Huvirgalt #" << counter <<":\n";
        counter = counter + 1;
        printMatrix(A);
        /*
        cout << "X uud:\n";
        for(auto i : x){
            for(float j : i)
                cout << j << " ";
            cout << "\n";
        }
        cout << "\n";
        */
    }

}

/*
void equation(vector<vector<float>>& A, vector<vector<float>>& x){
    vector<int> twos;
    for (int j = 1; j <= M; j++) {
        bool has_two = false;
        for (int i = 1; i <= N; i++) {
            if (x[i][j] == 2) {
                has_two = true;
                twos.push_back(i);
                break;
            }
        }

        if (has_two) {
            for (int i = 1; i <= N; i++) {
                if (x[i][j] == 1 || x[i][j] == 2) {
                    x[i][j] = x[0][j] * A[i - 1][j - 1]; 
                }
            }
        }
        else {
            for (int i = 1; i <= N; i++) {
                x[i][j] = NAN;
            }
        }
    }

    //
    int j ;
    for (int i = 1; i <= N; i++) {
        for (j = 1; j <= M; j++) {
            if(isnan(x[i][j])){
                cout << "x" << j <<"*("<<A[i-1][j-1]<< ") ";
            }
            else{
                cout << x[i][j] << " ";
            }
            if(j == 1){
                cout << "+ ";
            }
            else if (j == M){

            }
            else {
                cout << "+ ";
            }
        }
        cout << " = x" <<twos[i - 1]<< "\n";
    }
}
*/
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
    cout << "\nsystemuud\n";
    equation(mat,x);

    return 0;
}
