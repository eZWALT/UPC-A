 #include <iostream>
 #include <vector>
 using namespace std;

 int fibonacci(int n){
    if(n == 0) return 0;
    if(n == 1) return 1;
    vector<int> f(n+2 , 0);
    f[0] = 0;
    f[1] = 1;

    for(int i = 2; i <=n; ++i){
        f[i] = f[i-1] + f[i-2];
    }
    return f[n];
 }


 int main(){
    int n;
    while(cin >> n){
        cout << fibonacci(n) % (100000000+7) << endl;
    }
 } 
