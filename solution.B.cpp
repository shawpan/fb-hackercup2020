// #include <bits/stdc++.h>
#include "stdc++.h"

using namespace std;
using ll = long long;

ll fmax(ll a, ll b) {
    return a>b ? a : b;
}

ll fmin(ll a, ll b) {
    return a<b ? a : b;
}

ll gcd(ll a, ll b) {
    if(a<b) return gcd(b,a);
    while(a%b) {
        ll t = a%b;
        a=b;
        b=t;
    }
    return b;
}

bool isPrime(ll n) {
    if(n <= 2) return n == 2; 
    
    if(n%2 == 0) return false;
    
    for(ll i=3; i*i<=n; i+=2) {
        if(n%i == 0) return false;
    }
    
    return true;
}

bool isImpossible (string C, ll n) {
    ll countA = 0;
    ll countB = 0;
    for (ll i = 0; i < n; i++) {
        if (C[i] == 'B') {
            countB++;
        } else {
            countA++;
        } 
    }
    ll half = n / 2;
    
    return countA < half || countB < half;
}

string icase() {
    ll n;
    cin>>n;
    string C;
    cin>>C;
    
    if(isImpossible(C, n)) {
        return "N";
    }
    
    return "Y";
}

// void precal() {
// } 

void fileIO() {
    // string fileName = "sample_input";
    string fileName = "B";
    string inputFileName = fileName + ".txt";
    string outputFileName = fileName + "_output.txt";
	freopen (inputFileName.c_str(),"r",stdin);
	freopen (outputFileName.c_str(),"w",stdout);
}

int main() {
	fileIO();
    // precal();
    
    int t;
    cin>>t;
    ll cs=1;
    while(t--) {
         cout<<"Case #"<<cs++<<": "<<icase()<<endl;
        // cout<<"Case #"<<cs++<<": "<<endl;
        // printf("%.12Lf\n", icase());
        // icase();
        // cout<<icase()<<endl;
    }
    // cout<<icase()<<endl;
    // icase();
    return 0;
}