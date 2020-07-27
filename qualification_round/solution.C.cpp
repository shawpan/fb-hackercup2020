
// #include <bits/stdc++.h>
#include "stdc++.h"
#include <unordered_map>

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

struct Log {
    ll p, h;
    Log() {
        p = 0;
        h = 0;
    }
    Log(ll _p, ll _h) {
        p = _p;
        h = _h;
    }
};

bool cmp(const Log& log1, const Log& log2) {
    return log1.p < log2.p;
}

ll calclAns(vector<Log>& logs, ll n) {
    sort(logs.begin(), logs.end(), cmp);
    unordered_map<ll,ll> timber;
    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        Log aLog = logs[i];
        ll rightFall = timber[aLog.p] + aLog.h;
        ll leftFall = timber[aLog.p - aLog.h] + aLog.h;
        
        timber[aLog.p + aLog.h] = fmax(timber[aLog.p + aLog.h], rightFall);
        timber[aLog.p] = fmax(timber[aLog.p], leftFall);
        ans = fmax(ans, fmax( timber[aLog.p + aLog.h],  timber[aLog.p]) ) ;
    }
    
    return ans;
}

ll icase() {
    ll n;
    cin>>n;
    vector<Log> logs(n);
    for (ll i = 0; i < n; i++) {
        cin >> logs[i].p >> logs[i].h;
    }
    
    return calclAns(logs, n);
}

// void precal() {
// } 

void fileIO() {
    // string fileName = "sample_input";
    string fileName = "C";
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