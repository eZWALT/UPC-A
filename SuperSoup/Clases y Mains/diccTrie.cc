#include <iostream>
#include <vector>
#include "trie.cc"
#include <ctime>
#include<set>
using namespace std;

typedef vector<vector<char>> Matrix;

inline bool valid(Matrix &m, unsigned int i, unsigned int j)
{
    return i >= 0 and i < m.size() and j >= 0 and j < m[0].size();
}


void backtrack(Trie& t, Matrix& m, int i, int j, string part_word, vector<vector<bool>>& mb, int k, set<string>& foundWords, int& calls) {
    //Descartamos las posiciones que no podemos visitar y ya hemos visitado
    if (not (valid(m,i,j) and not mb[i][j])) return;
        
    ++calls;
    part_word += m[i][j];

    //Buscamos la palabra en la estructura y hacemos una poda en el caso de que no 
    //exista ninguna palabra que empice por el prefijo actual
    Trie t2 = t.prefix(part_word, k);

    if (t2.isEmpty()) return;

    mb[i][j] = true;
    if (t2.find_word(part_word, k)) foundWords.insert(part_word);
    
    //Llamadas recursivas de backtraking
    backtrack(t2,m,i+1,j,part_word, mb, k+1, foundWords, calls);
    backtrack(t2,m,i-1,j,part_word, mb, k+1, foundWords, calls);
    backtrack(t2,m,i,j+1,part_word, mb, k+1, foundWords, calls);
    backtrack(t2,m,i,j-1,part_word, mb, k+1, foundWords, calls);
    backtrack(t2,m,i+1,j+1,part_word, mb, k+1, foundWords, calls);
    backtrack(t2,m,i+1,j-1,part_word, mb, k+1, foundWords, calls);
    backtrack(t2,m,i-1,j-1,part_word, mb, k+1, foundWords, calls);
    backtrack(t2,m,i-1,j+1,part_word, mb, k+1, foundWords, calls);

    part_word.pop_back();
    mb[i][j] = false;

}



void solveSoup(int soupSize, Matrix& Soup, Trie& t, int diccSize, set<string>& foundWords, int& calls) {
    vector<vector<bool>> mb (soupSize, vector<bool>(soupSize, false));
    for (int i = 0; i < soupSize; ++i) {
        for (int j = 0; j < soupSize; ++j) {
            backtrack(t,Soup,i,j,"", mb, 0, foundWords, calls);
        }
    }
}

int main () {

    unsigned t0, t1, t2;

    //Inicialización de variables
    t2 = clock();
    int soupSize, diccSize, calls, insertedSize, wordsMaxSize;
    cin >> soupSize >> diccSize >> insertedSize >> wordsMaxSize;
    calls = 0;

    //Inicialización de las estructuras
    set<string> foundWords;
    vector<string> v(diccSize);
    Trie t;
    for (string& s: v) {
        cin>>s;
        t.insert(s);
    }

    Matrix Soup (soupSize, vector<char>(soupSize));

    //Lectura de strings inútiles para el vector
    string dummy;
    for (int i = 0; i < insertedSize; ++i) cin >> dummy;

    //Lectura de la sopa
    for (auto& v: Soup) {
        for (char& c : v) cin>>c;
    }

    t0 = clock();
    solveSoup(soupSize, Soup, t, diccSize, foundWords, calls);
    t1 = clock();

    //Estadísticas finales
    double timeI = (double(t0-t2)/CLOCKS_PER_SEC);
    double timeE = (double(t1-t0)/CLOCKS_PER_SEC);
    double timeT = timeI + timeE;

    cout << "Tiempo de inicialización: " << timeI << endl;
    cout << "Tiempo de backtracking: " << timeE << endl;
    cout << "Tiempo total: " << timeT << endl;
    cout << "Numero de llamadas: " << calls << endl;
    cout << "Palabras encontradas: " << foundWords.size() << endl; 

}
