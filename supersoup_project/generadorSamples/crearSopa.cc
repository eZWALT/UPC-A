#include "crear_sopa.cc"
#include <iostream>
#include<vector>

int main() {
    int soupSize;
    std::cin >> soupSize;
    std::vector<std::string> dicc;

    std::string s;

    int k = 0;
    int n = 0;

    cin >> s;
    while (s != ".") {
        dicc.push_back(s);
        if (s.length() > k) k = s.length();
        cin >> s;
    }   

    n = dicc.size();
    vector <string> inserted(20);
    srand(time(NULL));
    for (int i = 0; i < 20; ++i) {
        inserted[i] = dicc[rand() % n];
    }

    Matrix M = crear_sopa(inserted, soupSize);

    cout << soupSize << " " << n << " " << 20 << " " << k << endl;
    for (std::string& s: dicc) cout << s << endl;
    for (std::string& s: inserted) cout << s << endl;
    print(M);
}