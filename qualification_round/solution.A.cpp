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

void disallowIncoming(vector<vector<int> >& p, int n, string I) {
    for (int i = 0; i < n; i++) {
        if (I[i] == 'N') {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    p[j][i] = 0;
                }
            }
        }
    }
}

void disallowOutgoing(vector<vector<int> >& p, int n, string O) {
    for (int i = 0; i < n; i++) {
        if (O[i] == 'N') {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    p[i][j] = 0;
                 }
            }
        }
    }
}

void print(vector<vector<int> >& p, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (p[i][j]) {
                cout<<'Y';
            } else {
                cout<<'N';
            }
        }
        cout<<endl;
    }
}

void initialize(vector<vector<int> >& p, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (abs(i-j) <= 1) {
                p[i][j] = 1;
            }
        }
    }
}

void connectL(vector<vector<int> >& p, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if ( p[i][k] && p[k][j] ) {
                    p[i][j] = 1;
                }
            }
        }
    }
}

void connect(vector<vector<int> >& p, int n) {
    for (int l = 0; l < n; l++) {
        connectL(p, n);
    }
}

void icase() {
    int n;
    cin>>n;
    string I;
    string O;
    cin>>I;
    cin>>O;

    vector<vector<int> > p(n, vector<int>(n, 0));

    initialize(p, n);
    
    disallowIncoming(p, n, I);

    disallowOutgoing(p, n, O);
    
    connect(p, n);

    print(p, n);
}

// void precal() {
// } 

void fileIO() {
    // string fileName = "sample_input";
    string fileName = "A";
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
        //  cout<<"Case #"<<cs++<<": "<<icase()<<endl;
        cout<<"Case #"<<cs++<<": "<<endl;
        // printf("%.12Lf\n", icase());
        icase();
        // cout<<icase()<<endl;
    }
    // cout<<icase()<<endl;
    // icase();
    return 0;
}