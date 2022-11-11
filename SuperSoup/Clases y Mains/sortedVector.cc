#include<vector>
#include<iostream>
#include<algorithm>

class sortedVector {

  public:

    sortedVector() {}

    sortedVector(int n) {
        vec = std::vector<std::string> (n);
    }

    void readVector() {
        int n = vec.size();

        for (int i = 0; i < n; ++i) {
            std::cin >> vec[i];
        }

        sort(vec.begin(), vec.end());
    }

    int search (std::string s, int l, int r) {
        return dycot(s, l, r);
    }    

    std::pair<int, int> prefixSubVector(std::string s, int l, int r) {
        int fst, snd;
        fst = dycot(s, l, r);
        ++s[s.length() - 1];
        snd = dycot(s, l, r);
        return {fst, snd};
    }

    
    std::string ithElem(int i) {
        return vec[i];
    }

    void printSubVec(int l, int r) {
        if (r >= vec.size()) r = vec.size() - 1;
        for (int i = l; i <= r; ++i) {
            std::cout << vec[i] << std::endl;
        }
    }

  private:

    std::vector<std::string> vec;

    int dycot(std::string s, int l, int r) {
        int m = (l + r)/2;
        if (vec[m] == s) return m;
        
        if (l >= r) return l;
        
        if (vec[m] > s) return dycot(s, l, m - 1);
        
        else return dycot(s, m + 1, r);
    }
};