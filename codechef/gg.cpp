Skip to content
Search or jump to…
Pull requests
Issues
Marketplace
Explore
 
@Krishjain2911 
Krishjain2911
/
armory
Public
forked from anishrajan25/armory
0
05
Code
Pull requests
Actions
Projects
Wiki
Security
Insights
Settings
armory/codechef/ATWNT Feb Long Challenge.cpp
@anishrajan25
anishrajan25 Create ATWNT Feb Long Challenge.cpp
Latest commit c44772a 5 days ago
 History
 1 contributor
113 lines (85 sloc)  2.04 KB
   
#include <bits/stdc++.h>

#define ll long long

using namespace std;

vector<vector<int>> tree;
vector<unordered_map<ll, ll>> lcmTree;
vector<set<pair<ll, ll>>> answered;
vector<int> children, branchEnd;


void computeLCM(int n) {
    for (auto x: tree[n]) {
    ll tmp = x;
    int bache = children[n];
    
    if (bache == 1) tmp = branchEnd[n];
    if (children[tmp] == 0) {
        lcmTree[n][bache]++;
        lcmTree[tmp][1]++;
        continue;
    }
    
    computeLCM(tmp);
    
    for (auto lcm: lcmTree[tmp]) {
        lcmTree[n][bache * lcm.first] += lcm.second;
    }
  }
}

void fastio() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

void setupVariables(int size) {
    tree.resize(size + 1);
    lcmTree.resize(size + 1);
    children.resize(size + 1, 0);
    branchEnd.resize(size + 1);
    answered.resize(size + 1);
}

void reduceStraightBranch(int n) {
    branchEnd[n] = n;
    int count = children[n];
    
    for (auto x: tree[n]) {
        
        reduceStraightBranch(x);
        
        if (count == 1) {
            branchEnd[n] = branchEnd[x];
        }
    }
}

int getWork(int v, int k) {
    int lm = -1;
    auto ans = answered[v].lower_bound(pair<ll, ll>{k, lm});
    
    if(ans != answered[v].end()) {
        if((*ans).first == k) {
            return (*ans).second;
        }
    }
    
    int brbd = k;
    for(auto lcm: lcmTree[v]) {
        int mul = lcm.second;
        if(k % lcm.first == 0) brbd -= (k / lcm.first) * mul;
    }
    answered[v].insert(pair<ll, ll>{k, brbd});

    return brbd;
}

int main() {
    fastio();
    
    int n, q;
    cin>>n;
    
    setupVariables(n);
    
    int i = 2;
    while(i <= n) {
        int parent;
        cin>>parent;
        children[parent] += 1;
        tree[parent].push_back(i++);
    }
    
    reduceStraightBranch(1);
    computeLCM(1);
    
    cin>>q;
    while(q--) {
        int v, k;
        cin>>v>>k;
        
        v = branchEnd[v];
        
        int res = getWork(v, k);
        
        cout<<res<<"\n";
    }
    
    return 0;
  getch();
}
""© 2021 GitHub, Inc.
Terms
Privacy
Security
Status
Docs
Contact GitHub
Pricing
API
Training
Blog
About
Loading complete""
