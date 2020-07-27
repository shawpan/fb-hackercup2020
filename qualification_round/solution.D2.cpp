// #include <bits/stdc++.h>
#include "stdc++.h"
#include <unordered_map>

using namespace std;
using ll = long long;

bool _debug = false;

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
    ll id, cost, pos, reach;
    City() {
        id = 0;
        cost = 0;
        pos = 0;
        reach = 0;
    }
    City(ll _id, ll _cost, ll _pos) {
        id = _id;
        cost = _cost;
        pos = _pos;
        reach = 0;
    }
    City(ll _id, ll _cost, ll _pos, ll _reach) {
        id = _id;
        cost = _cost;
        pos = _pos;
        reach = _reach;
    }
};

bool operator<(const City& city1, const City& city2) {
    return city1.cost > city2.cost;
}

const ll N = 1e6+10;
ll n, m, a, b;
ll costs[N];
ll parent[N];
ll height[N];
 
void calculateHi(ll i) {
    ll node = i;
    ll h = 0;
    while (height[node] == 0) {
        h++;
        node = parent[node];
    }
    h = height[node] + h;
    node = i;
    while (height[node] == 0) {
        height[node]=h--;
        node = parent[node];
    }   
} 

void calculateHeight() {
    for (ll i = 1; i <= n; i++) {
        height[i]=0;
    }
    height[1]=1;
    for (ll i = 1; i <= n; i++) {
        calculateHi(i);
    }
}

ll findLCA(ll nodeA, ll nodeB) {
    if (height[nodeA] > height[nodeB]) {
        return findLCA(nodeB, nodeA);
    }
    
    while (height[nodeB] > height[nodeA]) {
        nodeB = parent[nodeB];
    }
    while (nodeA != nodeB) {
        nodeA = parent[nodeA];
        nodeB = parent[nodeB];
    }
    
    return nodeA;
}
    
vector<ll> findLine() {
    vector<ll> line;

    calculateHeight();
    ll lca = findLCA(a, b);
    ll node = a;
    while(node != lca) {
        line.push_back(node);
        node = parent[node];
    }
    line.push_back(lca);
    node = b;
    stack<ll> s;
    while(node != lca) {
        s.push(node);
        node = parent[node];
    }
    while(!s.empty()) {
        line.push_back(s.top());
        s.pop();
    }
    
    return line;
}

ll actualPos(ll pos, ll initialPos) {
    return initialPos - (pos - initialPos);
}

bool updateReach(ll skip[],
                    priority_queue<City>& pq, 
                    ll& cost, ll& reach, City& aCity, ll initialCityId) {
    vector<City> temp;
   
    while (!pq.empty()) {
        City cityUsedToRefuel = pq.top();
        temp.push_back(cityUsedToRefuel);
        pq.pop();
        // if (skip[cityUsedToRefuel.id] == 0 || cityUsedToRefuel.id == initialCityId) {
        //     // pq.push(cityUsedToRefuel);
        //     return false;
        // }
        if( aCity.pos < cityUsedToRefuel.pos + m) {
            reach = cityUsedToRefuel.pos + m;
            cost = cityUsedToRefuel.cost;
            // pq.push(cityUsedToRefuel);
            break;
        }
    }
    bool pqEmpty = pq.empty();
    for (ll i = 0; i < temp.size(); i++) {
        pq.push(temp[i]);
    }
    //if (!pq.empty() && skip[city1.id] && pos - skip[city1.id] - 1 > aCity.pos - pos) {
    
   return !pqEmpty;     
}

void addOptions( vector<vector<ll> >& graph, 
                ll skip[],
                priority_queue<City>& pq, 
                vector<ll>& line, 
                ll pos, ll reach, ll cost) {
                    
    vector<bool> visited(n + 1);
    queue<City> q;
    q.push(City(line[pos], cost, pos, reach));
    
    while(!q.empty()) {
        City aCity = q.front();
        cost = aCity.cost;
        reach = aCity.reach;
        q.pop();
        ll u = aCity.id;
        visited[u] = true;
        if(costs[aCity.id] > 0) {
            pq.push( City(aCity.id, cost + costs[aCity.id], actualPos(aCity.pos, pos), reach ) );
        }
        if(aCity.pos == reach && aCity.pos + 1 < pos + m) {
            if(_debug) cout << "Prev cost, reach " << cost << " " << reach << endl;
            if( !updateReach(skip, pq, cost, reach, aCity, line[pos]) ) {
                continue;
            }
            if(_debug) cout << "New cost, reach " << cost << " " << reach << endl;
        }
        
        
        for (ll i = 0; i < graph[u].size(); i++) {
            ll v = graph[u][i];
            if( !visited[v] && skip[v] == 0) {
                q.push(City(v, cost, aCity.pos + 1, reach));                
            }
        }   
    }
}

void buildGraph(vector<vector<ll> >& graph) {
    for (ll i = 1; i <= n; i++) {
        graph[i].push_back(parent[i]);
        graph[parent[i]].push_back(i);
    }
}

void buildSkip(vector<ll>& line, ll skip[]) {
    for (ll i = 0; i < line.size(); i++) {
        skip[line[i]] = i + 1;
    }
}

ll calculatelMinCost() {
    vector<ll> line = findLine();
    
    ll skip[N] = {0};
    buildSkip(line, skip);
    
    vector<vector<ll> > graph(n + 1);
    buildGraph(graph);
    
    vector<ll> minCost(n, -1);
    priority_queue<City> pq;
    minCost[0] = 0;
    ll pos = 0;
    ll cost = 0;
    ll reach = m;
    while (pos < line.size()) {
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
        addOptions(graph, skip, pq, line, pos, reach, cost);
        pos++;
    }
    
    ll bPos = (ll)line.size() - 1;
    
    return minCost[bPos];
}

ll icase() {
    cin >> n >> m >> a >> b;
    
    for (ll i = 1; i <= n; i++) {
        cin >> parent[i] >> costs[i];
    }
    
    return calculatelMinCost();
}

// void precal() {
// } 

void fileIO() {
    // string fileName = "sample_input";
    string fileName = "D2";
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