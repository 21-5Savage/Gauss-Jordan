#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;


vector<vector<float>> read_file(string name){
    vector<vector<float>> A;
    ifstream file(name);
    int n,m;
    if(!file){
        cout << "Error reading file\n";
        return {};
    }
    file >> n >> m;

    A.assign(n, vector<float>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {  
            file >> A[i][j];
        }
    }
    return A;
}

void print_matrix(vector<vector<float>> A){
    for(auto n : A){
        for(float x : n){
            cout << x << "\t";
        }
        cout << "\n";
    }
    cout << "\n";
}

void copy_supply_demand(vector<vector<float>> &src, vector<vector<float>> &dst){
    for (int j = 0; j < src[0].size(); j++) {
        dst[0][j] = src[0][j];
    }
    for (int i = 1; i < src.size(); i++) { 
        dst[i][0] = src[i][0]; 
    }
}

void check_supply_demand(vector<vector<float>> A, float &supply_sum, float &demand_sum){
    supply_sum = 0, demand_sum = 0;
    for(int i = 0; i < A[0].size(); i++){
        demand_sum += A[0][i];
    }
    for(int j = 0; j < A.size(); j++){
        supply_sum += A[j][0];
    }
}
void bituu_bolgoh(vector<vector<float>> &A){
    float supply_sum = 0, demand_sum = 0;

    check_supply_demand(A, supply_sum, demand_sum);

    if(demand_sum == supply_sum){
        return;
    }
    else if(demand_sum > supply_sum){
        //add row
        vector <float> row(A[0].size(), 0.0f);
        row[0] = demand_sum - supply_sum;
        A.push_back(row);
    }
    else if(supply_sum > demand_sum){

        //add column
        for (auto& row : A) {
            row.push_back(0.0f);
        }
        A[0].back() = supply_sum - demand_sum;
    }
}

vector<vector<float>> set_zeroes(vector<vector<float>> matrix) {
    vector<vector<float>> A = matrix;
    int n = A.size();
    int m = A[0].size();
    
    for (int i = 1; i < n; i++) {  
        if (A[i][0] == 0) {
            for (int j = 1; j < m; j++) {  
                A[i][j] = 0;
            }
        }
    }
    
    for (int j = 1; j < m; j++) {  
        if (A[0][j] == 0) {
            for (int i = 1; i < n; i++) {  
                A[i][j] = 0;
            }
        }
    }
    return A;
}

float max_in_row(const vector<vector<float>> matrix, int row_index) {
    vector<vector<float>> A = set_zeroes(matrix);
    //print_matrix(A);
    return *max_element(A[row_index].begin() + 1, A[row_index].end());
}

float max_in_column(const vector<vector<float>>& matrix, int column_index) {
    vector<vector<float>> A = set_zeroes(matrix);

    for(int i = 1; i < A.size(); i++){
        if(A[i][0] == 0){
            for(int j = 1; j < A[0].size(); j++){
                A[i][j] = 0;
            }
        }
    }

    float max_val = A[1][column_index];  
    for (int i = 2; i < A.size(); i++) { 
        max_val = max(max_val, A[i][column_index]);
    }
    return max_val;
}

bool no_expense(const vector<vector<float>>& A) {
    int n = A.size();   // row count
    int m = A[0].size(); // column count

    for (int i = 1; i < n; i++) {     
        for (int j = 1; j < m; j++) {  
            if (A[i][j] != 0) {
                return false; // Found a non-zero element, return false
            }
        }
    }

    return true;
}

pair<int, int> find_max_negative(const vector<vector<float>> solution, const vector<vector<float>>A) {
    float max_negative = 0;  
    int max_row = -1, max_col = -1;  

    if(no_expense(solution)){
        for (int j = 0; j < A[0].size(); j++) {
            if (A[0][j] != 0) {
                max_col = j;
                break;
            }
        }
    
        for (int i = 0; i < A.size(); i++) {
            if (A[i][0] != 0) {
                max_row = i;
                break;
            }
        }
        return {max_row, max_col};
    }

    for (int i = 1; i < solution.size(); i++) {  
        for (int j = 1; j < solution[i].size(); j++) {  
            
            if (solution[i][j] < 0 && abs(solution[i][j]) == abs(max_negative)) {
                if(A[i][j] != 0 && A[i][j] < A[max_row][max_col]){
                    max_negative = solution[i][j];
                    max_row = i;  
                    max_col = j; 
                }
            }
            else if(solution[i][j] < 0 && abs(solution[i][j]) > abs(max_negative)){
                max_negative = solution[i][j];
                max_row = i;  
                max_col = j;
            }
        }
    }

    return {max_row, max_col};  
}

void allocate(vector<vector<float>> &allocated, int x, int y){
    if(allocated[x][0] >= allocated[0][y]){
        allocated[x][0] -= allocated[0][y];
        allocated[x][y] = allocated[0][y];
        allocated[0][y] = 0;
    }
    else{
        allocated[0][y] -= allocated[x][0];
        allocated[x][y] = allocated[x][0];
        allocated[x][0] = 0;
    }
}

#include <vector>
using namespace std;

vector<vector<float>> remove_zeros(vector<vector<float>> A) {
    vector<vector<float>> B = A;
    int n = B.size(); 
    int m = B[0].size(); 

    for (int i = n - 1; i >= 1; i--) {
        if (B[i][0] == 0) {
            B.erase(B.begin() + i); // remove row i
        }
    }

    for (int j = m - 1; j >= 1; j--) {
        if (B[0][j] == 0) {
            for (auto& row : B) {
                row.erase(row.begin() + j);  // remove column j
            }
        }
    }

    return B;
}


void iterate(vector<vector<float>> &A, vector<vector<float>> &allocated){
    //rassel method
    int n = A.size(); //row count
    int m = A[0].size(); //column count
    vector<vector<float>> solution(n, vector<float>(m)), buf(n, vector<float>(m));
    copy_supply_demand(A, solution);
    //delta unelgeenuudiig uusgeh
    for(int i = 1; i < n; i++){
        for(int j = 1; j < m; j++){
            if(A[0][j] != 0 && A[i][0] != 0){
                solution[i][j] = A[i][j] - max_in_column(A,j) - max_in_row(A,i);
            }
            
           //cout << A[i][j] << " - " << max_in_column(A,j)  << " - " << max_in_row(A,i) << " = " << A[i][j] - max_in_column(A,j) - max_in_row(A,i) << "\n";
        }
    }
    //zardliin unelgeenuudiig harah bol
    cout<<"zarldiin unelgeenuud\n";
    print_matrix(solution);
    auto [x,y] = find_max_negative(solution, A);
    //cout << x << "\t" << y << "\t" << solution[x][y] << "\n";

    allocate(allocated, x, y);
    copy_supply_demand(allocated, A);
 
    cout << "odoogoor huvaarilasan achaanuud\n";
    print_matrix(allocated);

    // buf = remove_zeros(A);
    cout << "eh husnegt\n";
    print_matrix(remove_zeros(A));
}

float compute_total(vector<vector<float>> A, vector<vector<float>> allocated){
    float sum = 0;
    for(int i = 1; i < A.size(); i++){
        for(int j = 1; j < A[0].size(); j++){
            sum += (A[i][j] * allocated[i][j]);
        }
    }
    return sum;
}

void base_solution(vector<vector<float>> &A){
    int n = A.size(); //row count
    int m = A[0].size(); //column count
    vector<vector<float>> allocated(n, vector<float>(m, 0));

    //heregtsee nuutsiig huulj bairshuulah
    copy_supply_demand(A,allocated);

    float supply_sum, demand_sum, i = 1;
    while(supply_sum != 0 || demand_sum != 0){
        cout << "iteration #" << i << "\n";
        iterate(A,allocated);
        check_supply_demand(allocated, supply_sum, demand_sum);
        i++;
    }
    if(supply_sum == 0 || demand_sum == 0){
        cout << "tulguur shiid oldson\nNiit zardal : " << compute_total(A, allocated) << "\n";
    }
}


int main(){
    vector<vector<float>> A = read_file("teever.txt");
    bituu_bolgoh(A);
    print_matrix(A);
    cout <<"\n";
    base_solution(A);
    return 0;
}