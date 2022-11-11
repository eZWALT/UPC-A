#include "sortedVector.cc"
#include <set>
#include <ctime>
using namespace std;

typedef vector<vector<char>> Matrix;

bool isPrefix(string pr, string s) {
    //Esta función sirve para comprobar si una palabra es prefijo de otra
    //Es necesaria para hacer las podas con el vector ordenado

    int len = pr.length();
    if (len >= s.length()) return false;
    for (int i = 0; i < len; ++i) {
        if (pr[i] != s[i]) return false;
    }
    return true;
}

void printWords(set<string>& S) {
    set<string>::const_iterator it = S.begin();
    while(it != S.end()) {
        cout << *it << endl;
        ++it;
    }
}

Matrix readMatrix(int soupSize) {
    Matrix M(soupSize, vector<char> (soupSize));
    for (uint i = 0; i < soupSize; ++i) {
        for (uint j = 0; j < soupSize; ++j) cin >> M[i][j];
    }

    return M;
}

void alternativeBacktrack(vector<vector<bool>>& B, Matrix& M, int i, int j, string s, string se, set<string>& foundWords, int calls, int soupSize) {
    if (i >= soupSize or j >= soupSize or i < 0 or j < 0) return;
    if (B[i][j]) return;
    
    ++calls;
    s += M[i][j];
    if (s == se) foundWords.insert(s);
    if (not isPrefix(s, se)) return;

    B[i][j] = true;
    alternativeBacktrack(B, M, i, j + 1, s, se, foundWords, calls, soupSize);
    alternativeBacktrack(B, M,  i, j - 1, s, se, foundWords, calls, soupSize);
    alternativeBacktrack(B, M, i + 1, j + 1, s, se, foundWords, calls, soupSize);
    alternativeBacktrack(B, M,  i + 1, j - 1, s, se, foundWords, calls, soupSize);
    alternativeBacktrack(B, M,  i + 1, j, s, se, foundWords, calls, soupSize);
    alternativeBacktrack(B, M,  i - 1, j - 1, s, se, foundWords, calls, soupSize);
    alternativeBacktrack(B, M,  i - 1, j + 1, s, se, foundWords, calls, soupSize);
    alternativeBacktrack(B, M,  i - 1, j, s, se, foundWords, calls, soupSize);
    B[i][j] = false;
}

void alternativeSolveSoup(int soupSize, Matrix& Soup, sortedVector& sVec, int diccSize, set<string>& foundWords, int calls) {
    //Funcion parecida a solveSoup, pero que va buscando las palabras del diccionario de una a una en la sopa

    vector<vector <bool>> B (soupSize, vector<bool> (soupSize, false));
    for (int k = 0; k < diccSize; ++k) {
        string sk = sVec.ithElem(k);
        for (int i = 0; i  < soupSize; ++i) {
            for (int j = 0; j < soupSize; ++j) alternativeBacktrack(B, Soup, i, j, "", sk, foundWords, calls, soupSize); 
        }
    }
}

void backtrack(vector<vector<bool>>& B, Matrix& M, sortedVector& sVec, int i, int j, string& s, int fst, int snd, set<string>& foundWords, int& calls, int soupSize) {
    //Descartamos las posiciones que no podemos visitar y ya hemos visitado
    if (i >= soupSize or j >= soupSize or i < 0 or j < 0) return;
    if (B[i][j]) return;
    
    //Las llamadas solo las contamos si se hacen en posiciones aceptables
    ++calls;

    //Buscamos la palabra en la estructura y hacemos una poda en el caso de que no 
    //exista ninguna palabra que empice por el prefijo actual
    s += M[i][j];
    pair<int, int> p = sVec.prefixSubVector(s, fst, snd);
    if (sVec.ithElem(p.first) == s) foundWords.insert(s);
    if (p.first >= p.second and not isPrefix(s, sVec.ithElem(p.first))) {
        s.pop_back();
        return;
    }

    //Llamadas recursivas de backtraking
    B[i][j] = true;
    backtrack(B, M, sVec, i, j + 1, s, p.first, p.second, foundWords, calls, soupSize);
    backtrack(B, M, sVec, i, j - 1, s, p.first, p.second, foundWords, calls, soupSize);
    backtrack(B, M, sVec, i + 1, j, s, p.first, p.second, foundWords, calls, soupSize);
    backtrack(B, M, sVec, i + 1, j - 1, s, p.first, p.second, foundWords, calls, soupSize);
    backtrack(B, M, sVec, i + 1, j + 1, s, p.first, p.second, foundWords, calls, soupSize);
    backtrack(B, M, sVec, i - 1, j - 1, s, p.first, p.second, foundWords, calls, soupSize);
    backtrack(B, M, sVec, i - 1, j, s, p.first, p.second, foundWords, calls, soupSize);
    backtrack(B, M, sVec, i - 1, j + 1, s, p.first, p.second, foundWords, calls, soupSize);
    B[i][j] = false;
    s.pop_back();
}

void solveSoup(int soupSize, Matrix& Soup, sortedVector& sVec, int diccSize, set<string>& foundWords, int& calls) {
    //Matriz de booleanos para tener registro de que posiciones hemos visitado
    vector<vector <bool> > B (soupSize, vector<bool> (soupSize, false));
    string s;

    //Por cada casilla de la matriz iniciamos una llamada de backtracking
    for (int i = 0; i  < soupSize; ++i) {
        s = "";
        for (int j = 0; j < soupSize; ++j) backtrack(B, Soup, sVec, i, j, s, 0, diccSize - 1, foundWords, calls, soupSize); 
    }
}

int main() {

    unsigned t0, t1, t2;
    
    //Inicialización de variables
    t2 = clock();
    int soupSize, diccSize, calls, insertedSize, wordsMaxSize;
    cin >> soupSize >> diccSize >> insertedSize >> wordsMaxSize;
    calls = 0;

    //Inicialización de estructuras
    set<string> foundWords;
    sortedVector sVec(diccSize);
    sVec.readVector();

    //Lectura de strings inútiles para el vector
    string dummy;
    for (int i = 0; i < insertedSize; ++i) cin >> dummy;
    
    //Lectura de la sopa
    Matrix Soup = readMatrix(soupSize);

    //Solución de la sopa
    t0 = clock();
    solveSoup(soupSize, Soup, sVec, diccSize, foundWords, calls);
    //Alternative Solve soup utilitza un algoritmo alternativo que también hemos estado valorando
    //alternativeSolveSoup(soupSize, Soup, sVec, diccSize, foundWords, calls);
    t1 = clock();

    //Estadísticas finales (se puede descomentar printWords para ver que palabras ha encontrado)
    //printWords(foundWords) 
    double timeI = (double(t0-t2)/CLOCKS_PER_SEC);
    double timeE = (double(t1-t0)/CLOCKS_PER_SEC);
    double timeT = timeI + timeE;
    
    cout << "Tiempo de inicialización: " << timeI << endl;
    cout << "Tiempo de backtracking: " << timeE << endl;
    cout << "Tiempo total: " << timeT << endl;
    cout << "Numero de llamadas: " << calls << endl;
    cout << "Palabras encontradas: " << foundWords.size() << endl; 
}


