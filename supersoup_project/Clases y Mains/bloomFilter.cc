#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;
typedef struct {
    uint64_t a;
    uint64_t b;
} VH;
typedef vector<VH> H;

vector<uint64_t> PRIMES= {2,29, 677, 17579, 456979, 11881379, 308915797, 8031810211, 208827064597, 5429503679023, 141167095653379, 3670344486987793, 95428956661682197, 2481152873203736609};

class bloomFilter {
    private:
    int m; //size of the bit array 
    vector<bool> bitArray;
    int k; //number of hash functions
    int n; //number of inserted elements
    int maxSizeInserted; //size of the largest word inserted in the bitArray
    H hashes;


    //Hash functions
    int universalHashing(const string& key, const int number) const {
        int i = 0;
        int length = key.length();
        uint64_t hash = 0;

        while (i != length) {
            hash += key[i++];
            hash += hash << 10;
            hash ^= hash >> 6;
        }
        return ((hashes[number].a * hash + hashes[number].b) % PRIMES[maxSizeInserted]) % m;
    }

    uint64_t getRandom() const {
        uint64_t a = (uint64_t(rand() + rand() + (rand() % 2))) << 48;
        uint64_t b = (uint64_t(rand() + rand() + (rand() % 2))) << 32;
        uint64_t c = (uint64_t(rand() + rand() + (rand() % 2))) << 16;
        uint64_t d = (uint64_t(rand() + rand() + (rand() % 2))) << 0;
        return a + b + c + d;
    }

    void createHashes() {
        hashes.resize(k);
        for (int i = 0; i < k; ++i) {
            uint64_t a = getRandom();
            hashes[i].a = 1 + (a % (PRIMES[maxSizeInserted] - 1));
            uint64_t b = getRandom();
            hashes[i].b = b % (PRIMES[maxSizeInserted]);
        }
    }

    void insert(const string& word) {
        for (int i = 0; i < k; ++i) {
            int bitNumber = universalHashing(word, i);
            bitArray[bitNumber] = true;
        }
        ++n;
    }

    public:
    //Empty constructor
    bloomFilter() {}

    void print() const {
        cout << "m = " << m << ", k = " << k << ", n = " << n << ", probabilidad = " << this -> probability() << endl;
        //for (int i = 0; i < m; ++i) cout << bitArray[i] << " ";
        //cout << endl;
    }

    void setBestValues(const vector<string>& words, const double p, const int maxSize) {
        if (maxSize <= 13) maxSizeInserted = maxSize;
        else maxSizeInserted = 13;
        int size = words.size();
        m = ceil(-(size * log(p)) / pow(log(2),2));
        bitArray.resize(m);
        for (int i = 0; i < m; ++i) bitArray[i] = false;
        k = ceil((m * log(2)) / size);
        hashes.resize(k);
        this -> createHashes();
        //insert all words and set n        n = 0;   
        for (int i = 0; i < size; ++i) this -> insert(words[i]);
    }

    int largestword() const {
        return maxSizeInserted;
    }

    double probability() const {
        return pow((1 - pow(1 - (1.0 /m), k * n)), k);
    }

    bool isPresent(const string& word) const{
        bool isPresent = true;
        int i = 0;
        while (isPresent and i < k) {
            int bitNumber = universalHashing(word, i);
            if (not bitArray[bitNumber]) isPresent = false;
            ++i;
        }
    
        return isPresent;
    }
};