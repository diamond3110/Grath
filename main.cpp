#include <iostream>
#include <vector>
//0, 1, 0, 0, 0, 1,
//0, 0, 1, 0, 1, 0,
//0, 0, 0, 1, 0, 1,
//0, 0, 0, 1, 1, 0,
//0, 0, 0, 0, 0, 0,
//0, 0, 0, 0, 0, 0,

// 1,  1,  0,  0,  0,  0,  0,  0
//-1,  0,  1,  1,  0,  0,  0,  0
// 0,  0, -1,  0,  1,  1,  0,  0
// 0,  0,  0,  0, -1,  0,  1,  1
// 0,  0,  0, -1,  0,  0,  0, -1
// 0, -1,  0,  0,  0, -1,  0,  0

using namespace std;
vector<vector<int>> convertToIncidentMatrix(const vector<vector<int>>& matrix, int n, int column){
    vector<vector<int>> incidentMatrix(n, vector<int>(column));
    int dugs = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0 ; j < column; j++) {
            if(matrix[i][j] == 1){
                if(i!=j){
                    incidentMatrix[i][dugs] = 1;
                    incidentMatrix[j][dugs] = -1;
                }else{
                    incidentMatrix[i][dugs] = 1;
                }
                dugs++;
            }
        }
    }
    return incidentMatrix;
}
vector<vector<int>> convertToSmejnostMatrix(const vector<vector<int>>& matrix, int n, int column) {
    vector<vector<int>> smejnostMatrix(n, vector<int>(n));
    int m1, m2;
    bool b=false;
    for(int i = 0; i < column; i++){
        for(int j = 0; j < n; j++){
            if(matrix[j][i]==1){
                m1 = j;
            }
            if(matrix[j][i]==-1){
                m2 = j;
                b = true;
            }
        }
        if(b){
            smejnostMatrix[m1][m2] = 1;
        }else{
            smejnostMatrix[m1][m1] = 1;
        }
        b = false;
    }
    return smejnostMatrix;
}

vector<vector<int>> insertSpisok(int a){
    vector<vector<int>> smejnostMatrix(a, vector<int>(a));
    for(int i = 0; i < a; i++){
        cout<<"Введите количество дуг от точки "<<i+1<<endl;
        int b;
        cin>>b;
        for(int j = 0; j < b; j++){
            cout<<"Введите точку, к которой идет дуга "<<j+1<<" точки "<<i+1<<endl;
            int c;
            cin>>c;
            smejnostMatrix[i][c-1] = 1;
        }
    }
    return smejnostMatrix;
}

void printSpisoc(const vector<vector<int>>& matrix, int n){
    for(int i = 0; i < n; i++) {
        cout<<i+1<<": ";
        for (int j = 0; j < n-1; j++) {
            if(matrix[i][j]==1){
                cout<<j+1<<", ";
            }
        }
        if(matrix[i][n-1]==1){
            cout<<n<<";";
        }
        cout<<endl;
    }
}

int calcDugs(const vector<vector<int>>& matrix){
    int column = 0;
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            if(elem==1)
                column++;
        }
    }
    return column;
}

void printMatrix(const vector<vector<int>>& matrix, int n, int m) {
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m-1; j++){
            if(matrix[i][j]!=-1){
                cout<<" "<<matrix[i][j]<<", ";
            }else{
                cout<<matrix[i][j]<<", ";
            }
        }
        if(matrix[i][m-1]!=-1){
            cout<<" "<<matrix[i][m-1]<<endl;
        }else{
            cout<<matrix[i][m-1]<<endl;
        }

    }
}

int main() {
    system("chcp 65001");
    cout<<"Введите количество точек:"<<endl;
    int n;
    cin>>n;
    vector<vector<int>> matrix = insertSpisok(n);
    int column = calcDugs(matrix);
    vector<vector<int>> matrixIncident = convertToIncidentMatrix(matrix, n, column);
    cout<<"##########Матрица инцдентности##########"<<endl;
    printMatrix(matrixIncident, n, column);
    matrix = convertToSmejnostMatrix(matrixIncident, n, column);
    cout<<"##########Матрица смежности##########"<<endl;
    printMatrix(matrix, n, n);
    cout<<"##########Список смежности##########"<<endl;
    printSpisoc(matrix, n);
    return 0;
}
