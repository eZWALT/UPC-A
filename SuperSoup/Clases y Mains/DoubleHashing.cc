#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
using namespace std;

class DoubleDicc {

private:
    class DoubleHashingTable {
private:
    pair<int,string>* list;
    int capacityy;
    int ssize;
    int prime;
    long long pruebas = 0;
    long long busquedas = 0;

public:

    DoubleHashingTable(){}

    DoubleHashingTable(int n){
        int x = pow(2,log2(n));
        if(double(n)/double(x) > 0.75) x = x << 1;
        this->capacityy = x;

        vector<bool> isPrime(n,false);
        isPrime[0] = isPrime[1] = 1;
        for(long long i = 2; i*i <= n; i++)
            if(isPrime[i] == 0)
                for(long long j = i*i; j <= n; j += i)
                    isPrime[j] = 1;

        prime = n-1;
        while(not isPrime[prime]) --prime;

        this->ssize = 0;

        list = new pair<int,string> [capacityy];
        for(int i = 0; i < capacityy; ++i){
            list[i] = make_pair(-1,"");
        }
    }

    void fillTable(vector<string> vec){
        int n = vec.size();

        int x = pow(2,floor(log2(n))+1);
        if(double(n)/double(x) > 0.75) x = x << 1;
        this->capacityy = x;

        vector<bool> isPrime(n,false);
        isPrime[0] = isPrime[1] = 1;
        for(long long i = 2; i*i <= n; i++)
            if(isPrime[i] == 0)
                for(long long j = i*i; j <= n; j += i)
                    isPrime[j] = 1;

        prime = n-1;
        while(not isPrime[prime]) --prime;

        this->ssize = 0;

        list = new pair<int,string> [capacityy];

        for(int i = 0; i < capacityy; ++i){
            list[i] = make_pair(-1,"");
        }
        for(string s: vec) this->insert(s);
    }


    int hashStringtoInt(const string& clau){
        int i = 0;
        int hash = 0;
        int size = clau.length();

        while(i != size){
            hash += clau[i++];
            hash += hash << 10;
            hash ^= hash >> 6;
        }

        hash += hash << 3;
        hash ^= hash >> 11;
        hash += hash << 15;
        return (hash);
    }

    int hash1(int k) {
        return abs(k%capacityy);
    }


    int hash2(int k) {
        int x = prime - k%prime;
        if(x%2==0) ++x;
        return abs(x);
    }

    int hash_probe(int k, int i){
        return ((hash1(k) + i * hash2(k)) % capacityy);
    }

    int insert(const string& value){

       if(ple()){
         cout << "OVERFLOW" << endl;
         exit(-1);
      }

      if(search(value)) return -1;

      int k = hashStringtoInt(value);
      int i = 0,j;
      while(i != capacityy){
         j = hash_probe(k,i);
         if(list[j].first == -1){
            list[j] = make_pair(k,value);
            ++ssize;
            return j;
         }
         else ++i;
      }

      return -1;
    }

    bool search(const string& value){
        ++busquedas;
        int k = hashStringtoInt(value);
        int i = 0,j = hash1(k);
        ++pruebas;

        while(list[j].second != value){
            //cout << value << " " << hash1(k) << " " << hash2(k) << " " << hash_probe(k,i) << " " << i << endl;
            if(list[j].first == -1){
                return false;
            }
            ++i;
            j = hash_probe(k,i);
            ++pruebas;
         }

         return true;

    }

    int size(){
        return this->ssize;
    }

    int capacity(){
        return this->capacityy;
    }

    bool buit(){
        return this->ssize == 0;
    }

    bool ple(){
        return this->ssize == this->capacityy;
    }

    void imprimir(){

        for(int i = 0; i < this->capacityy; ++i){
            if(list[i].first != -1){
                cout << "Key = " << list[i].first << " Value= " << list[i].second << endl;
            }
        }
    }

    double load_factor(){
        return double(ssize)/double(capacityy);
    }

    double expected_successful_search(){
        return (1.0 /load_factor()) * log2(expected_unsuccessful_search());
    }

    double expected_unsuccessful_search(){
        return 1.0 / (1.0 - load_factor());
    }

    void info(){
        cout << "busquedas: " << busquedas << endl;
        cout << "pruebas: " << pruebas << endl;
        cout << "promedio: " << double(pruebas)/double(busquedas) << endl;
        cout << "Promedio busqueda exitosa " << this->expected_successful_search() << endl;
        cout << "Promedio busqueda sin exito "  << this->expected_unsuccessful_search() << endl;
    }


};

    DoubleHashingTable words;
    DoubleHashingTable prefixes;
public:

    DoubleDicc();

    DoubleDicc(vector<string>& v){
        int size = v.size();
        words.fillTable(v);

        int prefixsize = 0;
        for(int i = 0; i < size; ++i){
            prefixsize += v[i].length() - 1;
        }
        vector<string> pf(0);

        for(string s: v){
            for(int i = 1; i < s.length(); ++i) pf.push_back(s.substr(0,i));
        }

        prefixes.fillTable(pf);
    }

        DoubleDicc(const vector<string>& v,const vector<string>& p){
        words.fillTable(v);
        prefixes.fillTable(p);
    }

    bool prefixSearch(const string& s){
        return prefixes.search(s);
    }

    bool wordSearch(const string& s){
        return words.search(s);
    }

    void printWords(){
        words.imprimir();
    }

    void printPrefixes(){
        prefixes.imprimir();
    }

    void displayStatistics(){
        words.info();
        prefixes.info();
    }

};

