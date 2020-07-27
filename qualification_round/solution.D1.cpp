// #include <bits/stdc++.h>
#include "stdc++.h"
// #include <unordered_map>

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

class City {
public:
    ll cost, pos;
    City() {
        cost = 0;
        pos = 0;
    }
    City(ll _cost, ll _pos) {
        cost = _cost;
        pos = _pos;
    }
};

bool operator<(const City& city1, const City& city2) {
    return city1.cost > city2.cost;
}

ll calculatelMinCost(vector<ll>& costs, ll n, ll m) {
    vector<ll> minCost(n, -1);
    priority_queue<City> pq;
    minCost[0] = 0;
    ll pos = 0;
    ll cost = 0;
    ll reach = m;
    while (pos < n) {
        if(pos > reach) {
            if(pq.empty()) {
                break;
            }
            City aCity = pq.top();
            pq.pop();
            reach = aCity.pos + m;
            cost = aCity.cost;
            continue;
        }
        minCost[pos] = cost;
        if(costs[pos] > 0) {
            pq.push( City(cost + costs[pos], pos) );
        }
        pos++;
    }
    
    
    return minCost[n-1];
}

ll icase() {
    ll n, m;
    cin >> n >> m;
    vector<ll> costs(n);
    for (ll i = 0; i < n; i++) {
        cin >> costs[i];
    }
    
    return calculatelMinCost(costs, n, m);
}

// void precal() {
// } 

void fileIO() {
    // string fileName = "sample_input";
    string fileName = "D1";
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