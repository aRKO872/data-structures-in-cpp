// Print number of strongly connected components (Kosaraju) :
void dfs (vector<vector<int>>& graph, stack<int>& topoSt, vector<int>& vis, int src) {
    vis[src] = 1;
    
    for (auto nbr: graph[src]) {
        if (vis[nbr] == 0) {
            dfs (graph, topoSt, vis, nbr);
        }
    }
    
    topoSt.push(src);
}

void dfsTrav (vector<vector<int>>& graph, vector<int>& vis, int src) {
    vis[src] = 1;
    
    for (auto nbr: graph[src]) {
        if (vis[nbr] == 0) {
            dfsTrav (graph, vis, nbr);
        }
    }
}

int kosaraju(int V, vector<vector<int>>& edges)
{
    //code here
    stack<int> topoSt;
    vector<int> visited (V, 0);
    
    for (int i = 0; i < V; i++) {
        if (visited[i] == 0) {
            dfs (edges, topoSt, visited, i);
        }
    }
    
    vector<vector<int>> graph (V, vector<int>());
    for (int i = 0; i < V; i++) {
        for (auto edge: edges[i]) {
            graph[edge].push_back(i);
        }
    }
    
    vector<int> vis (V, 0);
    int count = 0;
    while (!topoSt.empty()) {
        int s = topoSt.top(); topoSt.pop();
        if (vis[s] == 0) {
            count++;
            dfsTrav (graph, vis, s);
        }
    }
    
    return count;
}

// Number of Bridges (Tarjan's algo) :
void dfs (int src, int par, int& timer, vector<vector<int>>& graph, vector<int>& vis, vector<int>& tin, vector<int>& low, vector<vector<int>>& ans) {
    vis[src] = 1;
    tin[src] = timer;
    low[src] = timer;
    timer++;

    for (auto nbr : graph[src]) {
        if (nbr == par) continue;
        if (vis[nbr] == 0) {
            dfs (nbr, src, timer, graph, vis, tin, low, ans);

            low[src] = min (low[src], low[nbr]);
            if (low[nbr] > tin[src]) {
                ans.push_back({src, nbr});
            }
        } else {
            low[src] = min (low[src], low[nbr]);
        }
    }
}
vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
    vector<vector<int>> graph (n, vector<int> ());

    for (auto arr: connections) {
        graph[arr[0]].push_back(arr[1]);
        graph[arr[1]].push_back(arr[0]);
    }

    vector<vector<int>> ans;
    vector<int> visited (n);
    int timer = 0;
    vector<int> tin (n);
    vector<int> low (n); 
    dfs (0, -1, timer, graph, visited, tin, low, ans);

    return ans;
}