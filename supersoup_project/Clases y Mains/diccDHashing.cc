#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>
#include <bits/stdc++.h>
#include <ctime>
#include "DoubleHashing.cc"
using namespace std;

typedef vector<vector<char>> Matrix;
//MAMASITA ET AL. GALACTIC FAST SUPERSOUP SOLVING ALGORITHM

void backtracking (DoubleDicc& T, const Matrix& M,vector<vector<bool>>& B,int N, int i,int j, string& s, set<string>& solution, int& calls){
    //Descartamos las posiciones que no podemos visitar y ya hemos visitado
    if(i >= N or j >= N or i < 0 or j < 0) return;
    if(B[i][j]) return;

    ++calls;

    //Buscamos la palabra en la estructura y hacemos una poda en el caso de que no 
    //exista ninguna palabra que empice por el prefijo actual
    s+= M[i][j];
    bool found = T.wordSearch(s);
    if(found) solution.insert(s);
    if(not found and not T.prefixSearch(s)) {
        s.pop_back();
        return;
    }

    //Llamadas recursivas de backtraking
    B[i][j] = true;
    backtracking(T,M,B,N,i-1,j-1,s,solution,calls);
    backtracking(T,M,B,N,i-1,j,s,solution,calls);
    backtracking(T,M,B,N,i-1,j+1,s,solution,calls);
    backtracking(T,M,B,N,i,j-1,s,solution,calls);
    backtracking(T,M,B,N,i,j+1,s,solution,calls);
    backtracking(T,M,B,N,i+1,j-1,s,solution,calls);
    backtracking(T,M,B,N,i+1,j,s,solution,calls);
    backtracking(T,M,B,N,i+1,j+1,s,solution,calls);
    B[i][j] = false;
    s.pop_back();
}


void solveSoup(DoubleDicc& T, const Matrix& M, set<string>& solution, int& calls){
    int N = M.size();
    vector<vector<bool>> B(N, vector<bool> (N,false));
    string s;

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j){
            s = "";
            backtracking(T,M,B,N,i,j,s,solution, calls);
        }
    }
}

void read_sopita(Matrix& m){
    for(int i = 0; i < m.size();++i){
        for(int j = 0; j < m.size(); ++j){
            cin >> m[i][j];
        }
    }
}

Matrix readMatrix(int Nm) {
    Matrix M(Nm, vector<char> (Nm));
    for (uint i = 0; i < Nm; ++i) {
        for (uint j = 0; j < Nm; ++j) cin >> M[i][j];
    }

    return M;
}


int main(){
    unsigned t0, t1, t2;

    //Inicialización de variables
    t2 = clock();
    int soupsize,diccsize,subsetsize,maxlength, calls;
    string entrada;
    cin >> soupsize >> diccsize >> subsetsize >> maxlength;
    calls = 0;
    
    //Inicialización de estructuras
    vector<string> palabras(0);
    vector<string> prefijos(0);
    set<string> solution;

    for(int k = 0; k < diccsize; ++k){
        cin >> entrada;
        palabras.push_back(entrada);
        int len = entrada.length();
        for(int i = 1; i < len; ++i) prefijos.push_back(entrada.substr(0,i));

    }
    DoubleDicc Dhash(palabras,prefijos);
    
    //Lectura de strings inútiles para el DHashing
    string s;
    for (int i = 0; i < subsetsize; ++i) cin >> s;

    //Lectura de la sopa
    Matrix soup = readMatrix(soupsize);

    //Solución de la sopa
    t0 = clock();
    solveSoup(Dhash,soup,solution, calls);
    t1 = clock();

    //Estadísticas finales (Si se descomenta displayStatistics() se pueden ver más resultados)
    double timeI = (double(t0-t2)/CLOCKS_PER_SEC);
    double timeE = (double(t1-t0)/CLOCKS_PER_SEC);
    double timeT = timeI + timeE;

    cout << "Tiempo de inicialización: " << timeI << endl;
    cout << "Tiempo de backtracking: " << timeE << endl;
    cout << "Tiempo total: " << timeT << endl;
    cout << "Numero de llamadas: " << calls << endl;
    cout << "Palabras encontradas: " << solution.size() << endl; 

    //DHash.displayStatistics();
}
