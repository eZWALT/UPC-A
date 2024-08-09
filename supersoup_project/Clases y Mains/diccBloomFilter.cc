#include<iostream>
#include<vector>
#include<set>
#include <ctime>
#include <bits/stdc++.h>
#include "bloomFilter.cc"

typedef vector<char> VC;
typedef vector<VC> VVC;

VVC soup;
bloomFilter bloomDic;
bloomFilter prefixes;
set<string> dicWithoutRep;
vector<string> dic;
vector<string> insertedWords;
set<string> foundWords;

int numQueries = 0;
int falsopositivos = 0;
bool prefix = true;

double probability = 0.000001;

void inicialize() {
    int soupSize, dicSize, insertedSize, wordsMaxSize;
    cin >> soupSize >> dicSize >> insertedSize >> wordsMaxSize;

    //Leemos diccionario
    dic.resize(dicSize);
    for (int i = 0; i < dicSize; ++i) {
        cin >> dic[i]; 
        dicWithoutRep.insert(dic[i]);
    }

    //Leemos palabras a insertar
    insertedWords.resize(insertedSize);
    for (int i = 0; i < insertedSize; ++i) cin >> insertedWords[i];

    //Leemos soup
    soup.resize(soupSize, vector<char>(soupSize));
    for (int i = 0; i < soupSize; ++i)
        for (int j = 0; j < soupSize; ++j) cin >> soup[i][j];
    
    //Generamos el dic bloomFilter
    bloomDic.setBestValues(dic, probability, wordsMaxSize);

    //Generamos el bloomFilter de prefixes
    set<string> pre;
    for (int i = 0; i < dicSize; ++i) {
        int wordSize = dic[i].size();
        for (int j = 1; j < wordSize; ++j) {
            pre.insert(dic[i].substr(0,j));
        }
    }
    vector<string> aux(pre.size());
    int i = 0;
    for (set<string>::const_iterator it = pre.begin(); it != pre.end(); ++it) {
        aux[i] = *it;
        ++i;
    }

    prefix = aux.size() != 0;
    if (prefix) prefixes.setBestValues(aux, probability, wordsMaxSize - 1);

}

void backtrack(vector<vector<bool>>& visited, string& actualWord, int i, int j) {
    //Descartamos las posiciones que no podemos visitar y ya hemos visitado
    int size = soup.size();
    if (i >= size or j >= size or i < 0 or j < 0) return;
    if (visited[i][j]) return;
    if (int(actualWord.length()) > bloomDic.largestword()) return;
    
    ++numQueries;
    
    //Buscamos la palabra en la estructura y hacemos una poda en el caso de que no 
    //exista ninguna palabra que empice por el prefijo actual
    actualWord += soup[i][j];
    if (bloomDic.isPresent(actualWord)) {
        foundWords.insert(actualWord).second;

        //La comprobación de si es un falso positivo o no retrasa el programa y no es necesaria teniendo en cuenta
        //la baja probabilidad de falsos positivos actual (aunque lo hemos usado para hacer comprobaciones)
        //if (dicWithoutRep.find(actualWord) == dicWithoutRep.end()) ++falsopositivos;
    }
    if (prefix and not prefixes.isPresent(actualWord)) {
        actualWord.pop_back();
        return;
    }

    //Llamadas recursivas de backtraking
    visited[i][j] = true;
    backtrack(visited, actualWord, i, j + 1);
    backtrack(visited, actualWord, i, j - 1);
    backtrack(visited, actualWord, i + 1, j);
    backtrack(visited, actualWord, i + 1, j - 1);
    backtrack(visited, actualWord, i + 1, j + 1);
    backtrack(visited, actualWord, i - 1, j - 1);
    backtrack(visited, actualWord, i - 1, j);
    backtrack(visited, actualWord, i - 1, j + 1);
    actualWord.pop_back();
    visited[i][j] = false;
}

void solveSoup() {
    int size = soup.size();
    string actualWord;
    vector<vector<bool>> visited (size, vector<bool>(size, false));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            actualWord = "";
            backtrack(visited, actualWord, i, j);
        }
    }
}

int palabrasEncontradas() {
    int counter = 0;
    for (set<string>::const_iterator it = dicWithoutRep.begin(); it != dicWithoutRep.end(); ++it) {
        if (foundWords.find(*it) != foundWords.end()) ++counter;
    }
    return counter;
}

bool isCorrect() {
    bool correct = true;
    int size = insertedWords.size();
    int i = 0;
    while (correct and i < size) {
        correct = foundWords.find(insertedWords[i]) != foundWords.end();
        ++i;
    }
    return correct;
}

//Esta función muestra resultados adicionales exclusivos del bloom filter
void resultados() {
    cout << "Los valores del BloomFilter del diccionario: " << endl;
    bloomDic.print();
    cout << "Los valores del BloomFilter de los prefixes: " << endl;
    prefixes.print();

    cout << "Tamaño del diccionario: " << dic.size() << endl;
    cout << "Numero de palabras probadas: " << numQueries << endl;
    int dicFound = palabrasEncontradas();
    cout << "Numero de palabras encontradas del diccionario: " << dicFound << endl;

    cout << "Falsos positivos totales: " << falsopositivos << endl;
    //cout << "Numero de falsos positivos esperados: " << int (numQueries * bloomDic.probability()) << endl;

    if (isCorrect()) cout << "Se han encontrado todas las palabras insertadas en la soup" << endl;
    else cout << "Alguna palabra no ha sido encontrada en la soup" << endl;
}

int main() {
    unsigned t0, t1, t2;
    
    t2 = clock();
    inicialize();

    t0 = clock();
    solveSoup();
    t1 = clock();

    //Estadísticas finales (Si se descomenta resultados() se pueden ver más resultados)
    double timeI = (double(t0-t2)/CLOCKS_PER_SEC);
    double timeE = (double(t1-t0)/CLOCKS_PER_SEC);
    double timeT = timeI + timeE;
    int dicFound = palabrasEncontradas();

    cout << "Tiempo de inicialización: " << timeI << endl;
    cout << "Tiempo de backtracking: " << timeE << endl;
    cout << "Tiempo total: " << timeT << endl;
    cout << "Numero de llamadas: " << numQueries << endl;
    cout << "Palabras encontradas: " << dicFound << endl;

    //resultados()
}