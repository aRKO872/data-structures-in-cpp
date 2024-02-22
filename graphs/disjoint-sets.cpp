// Disjoint Sets CLass : 
class DisjointSet {
    vector<int> rank, par;
    public:
    DisjointSet (int n) {
        rank.resize(n+1, 0);
        par.resize(n+1);
        for (int i = 0; i <= n; i++) {
            par[i] = i;
        }
    }
    
    int findU(int x) {
        if (par[x] == x) return x;
        return par[x] = findU (par[x]);
    }
    
    void union_rank (int u, int v) {
        int ulp_u = findU (u);
        int ulp_v = findU (v);
        
        if (ulp_u == ulp_v) return;
        else if (rank[ulp_u] > rank[ulp_v]) {
            par[ulp_v] = ulp_u;
            ulp_u++;
        } else if (rank[ulp_u] < rank[ulp_v]) {
            par[ulp_u] = ulp_v;
            ulp_v++;
        } else {
            par[ulp_u] = ulp_v;
            ulp_v++;
        }
    }
};

// Using Disjoint Set to find Minimum Spanning Tree (Kruskal's Algo) :
int spanningTree(int V, vector<vector<int>> adj[]){

    vector<vector<int>> graph;
    for (int i = 0; i < V; i++) {
        for (auto arr: adj[i]) {
            graph.push_back({i, arr[0], arr[1]});
        }
    }
    
    sort(graph.begin(), graph.end(), [](vector<int>& arr1, vector<int>& arr2) {
        return arr1[2] < arr2[2];
    });
    
    int minWt = 0;
    DisjointSet ds (V);
    for (auto arr: graph) {
        if (ds.findU(arr[0]) == ds.findU(arr[1])) continue;
        ds.union_rank(arr[0], arr[1]);
        minWt += arr[2];
    }
    
    return minWt;
}

// Number of Operations to Make Network Connected (Leetcode - Very Very Important question!)
void dfsTrav (vector<vector<int>>& graph, vector<int>& vis, int src) {
    vis[src] = 1;
    for (auto nbr: graph[src]) {
        if (vis[nbr] == 0) {
            dfsTrav (graph, vis, nbr);
        }
    } 
}
int makeConnected(int n, vector<vector<int>>& edges) {
    vector<vector<int>> graph (n, vector<int> ());

    for (auto arr: edges) {
        graph[arr[0]].push_back(arr[1]);
        graph[arr[1]].push_back(arr[0]);
    }

    vector<int> vis (n); int extraEdgesReqd = -1;
    for (int i = 0; i < n; i++) {
        if (vis[i] == 0) {
            extraEdgesReqd++;
            dfsTrav (graph, vis, i);
        }
    }

    DisjointSet ds (n);
    int extraEdges = 0;
    for (auto arr: edges) {
        if (ds.findU(arr[0]) == ds.findU(arr[1])) {
            extraEdges++;
        } else {
            ds.union_rank(arr[0], arr[1]);
        }
    }

    if (extraEdges < extraEdgesReqd) return -1;
    return extraEdgesReqd;
}

// Accounts Merge (VVVV Important Leetcode Question!)
vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    unordered_map<string, int> mp1;
    DisjointSet ds (accounts.size());
    for (int accNo = 0; accNo < accounts.size(); accNo++) {
        auto arr = accounts[accNo];
        for (int i = 1; i < arr.size(); i++) {
            if (mp1.find(arr[i]) == mp1.end()) {
                mp1[arr[i]] = accNo;
            } else {
                ds.union_rank(mp1[arr[i]], accNo);
            }
        }
    }

    map<int, set<string>> mp2;
    for (auto p: mp1) {
        int ult_par = ds.findU (p.second);
        mp2[ult_par].insert(p.first);
    }

    vector<vector<string>> ans;
    for (auto p: mp2) {
        vector<string> temp;
        temp.push_back(accounts[p.first][0]);
        for (auto mails: p.second) {
            temp.push_back(mails);
        }
        ans.push_back(temp);
    }

    return ans;
}