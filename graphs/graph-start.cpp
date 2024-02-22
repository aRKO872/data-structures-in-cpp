// DFS Of a Graph : 
void recSol (unordered_map<int, vector<int>>& graph, vector<int>& visited, vector<int>& ans, int V) {
    if (visited[V] == -1) return;
    
    visited[V] = -1;
    ans.push_back(V);
    
    for (auto i: graph[V]) {
        recSol (graph, visited, ans, i);
    }
}
vector<int> dfsOfGraph(int V, vector<int> adj[]) {
    // Code here
    unordered_map<int, vector<int>> graph;
    for (int arr = 0; arr < V; arr++) {
        graph[arr] = adj[arr];
    }
    vector<int> visited (V, 0);
    vector<int>ans;
    recSol (graph, visited, ans, 0);
    return ans;
}

// BFS Of a Graph :
vector<int> bfsOfGraph(int V, vector<int> adj[]) {
    // Code here
    queue<int> q;
    q.push(0);
    vector<int> visited (V, 0);
    visited[0] = 1;
    vector<int> ans;
    
    while (!q.empty()) {
        int vertex = q.front(); q.pop();
        ans.push_back(vertex);
        for (auto vertexNb: adj[vertex]) {
            if (visited[vertexNb] == 0) {
                visited[vertexNb] = 1;
                q.push(vertexNb);
            }
        }
    }
    
    return ans;
}

// Cycle Detection in Undirected Graph (using DFS) : 
 bool recSol (vector<int> adj[], vector<bool>& visited, int ind, int par) {
    visited[ind] = 1;
    
    for (auto i: adj[ind]) {
        if (visited[i] == 0) {
            if (recSol (adj, visited, i, ind)) return true;
        } else if (i != par) {
            return true;
        }
    }
    
    return false;
}
bool isCycle(int V, vector<int> adj[]) {
    // Code here
    vector<bool> visited (V, 0);
    vector<bool> temp = visited;
    for (int i = 0; i < V; i++) {
        if (recSol (adj, temp, i, -1)) return true;
        temp = visited;
    }
    return false;
}

// Cycle Detection in Undirected Graph (using BFS) : 
bool isCycle(int V, vector<int> adj[]) {
    // Code here
    for (int vert = 0; vert < V; vert++) {
        queue<pair<int, int>> q;
        q.push({vert, -1});
        vector<int> visited (V, 0);
        visited[vert] = true;
        
        while (!q.empty()) {
            auto topEle = q.front(); q.pop();
            int ind = topEle.first;
            int par = topEle.second;
            for (auto i : adj[ind]) {
                if (visited[i] == 0) {
                    visited[i] = 1;
                    q.push({i, ind});
                } else if (i != par) {
                    return true;
                }
            }
        }
    }
    
    return false;
}

// Cycle Detection in Directed Graph (using DFS and Backtracking) :
bool recSol (vector<int> adj[], vector<int>& visited, unordered_map<int, bool>& mp, int ind) {
    visited[ind] = 1;
    mp[ind] = true;
    
    for (auto i : adj[ind]) {
        if (visited[i] == 0) {
            if (recSol (adj, visited, mp, i)) {
                return true;
            }
        } else if (visited[i] == 1 && mp[i] == true) {
            return true;
        }
    }
    
    mp[ind] = false;
    return false;
}
bool isCyclic(int V, vector<int> adj[]) {
    // code here
    vector<int> visited (V, 0);
    vector<int> temp = visited;
    unordered_map<int, bool> mp;
    for (int i = 0; i < V; i++) {
        if (visited[i] == 0 && recSol (adj, temp, mp, i)) return true;
    }
    return false;
}

// Number of Islands : 
void recSol (vector<vector<char>>& grid, int i, int j) {
    grid[i][j] = '0';
    if (i-1 >= 0 && grid[i-1][j] == '1') recSol (grid, i-1, j);
    if (j-1 >= 0 && grid[i][j-1] == '1') recSol (grid, i, j-1);
    if (i+1 < grid.size() && grid[i+1][j] == '1') recSol (grid, i+1, j);
    if (j+1 < grid[0].size() && grid[i][j+1] == '1') recSol (grid, i, j+1);
}
int numIslands(vector<vector<char>>& grid) {
    int count = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '1') {
                count++;
                recSol (grid, i, j);
            }
        }
    }
    return count;
}

// Rotting Oranges : 
int orangesRotting(vector<vector<int>>& grid) {
    queue<pair<pair<int, int>, int>> q;
    int n = grid.size(), m = grid[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 2) q.push({{i, j}, 0});
        }
    } 

    int count = 0;
    while (!q.empty()) {
        auto topEle = q.front(); q.pop();
        int x = topEle.first.first, y = topEle.first.second, level = topEle.second;
        count = max (count, level);

        if (x-1 >= 0 && grid[x-1][y] == 1) {grid[x-1][y] = 2; q.push({{x-1, y}, level+1});}
        if (x+1 < n && grid[x+1][y] == 1) {grid[x+1][y] = 2; q.push({{x+1, y}, level+1});}
        if (y-1 >= 0 && grid[x][y-1] == 1) {grid[x][y-1] = 2; q.push({{x, y-1}, level+1});}
        if (y+1 < m && grid[x][y+1] == 1) {grid[x][y+1] = 2; q.push({{x, y+1}, level+1});}
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1) return -1;
        }
    } 

    return count;
}

// Find Eventual Safe States : 
bool dfs (vector<vector<int>>& graph, unordered_map<int, bool>& mp, vector<int>& vis, vector<int>& check, int src) {
    vis[src] = 1;
    mp[src] = true;
    check[src] = 0;

    for (auto nbr: graph[src]) {
        if (vis[nbr] == 0) {
            if (dfs (graph, mp, vis, check, nbr)) {
                return true;
            }
        } else if (mp[nbr]) {
            return true;
        }
    }

    mp[src] = false;
    check[src] = 1;
    return false;
}
vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
    vector<int> check (graph.size());
    vector<int> vis (graph.size());
    unordered_map<int, bool> mp;
    for (int i = 0; i < graph.size(); i++) {
        if (vis[i] == 0) {
            dfs (graph, mp, vis, check, i);
        }
    }
    vector<int> ans;
    for (int i = 0; i < check.size(); i++) {
        if (check[i] == 1) ans.push_back(i);
    }
    return ans;
}

// Word Ladder 2 : 
vector<vector<string>> findSequences(string beginWord, string endWord, vector<string>& wordList) {
    // code here
    queue<pair<vector<string>, int>> q;
    unordered_set<string> st (wordList.begin(), wordList.end());
    q.push({{beginWord}, 1});
    vector<vector<string>> ans;
    int prevLevel = -1;
    vector<string> toBeRemoved;
    toBeRemoved.push_back(beginWord);

    while (!q.empty()) {
        auto p = q.front(); q.pop();
        auto store = p.first; auto level = p.second;
        auto word = store.back();

        if (level != prevLevel) {
            for (auto i: toBeRemoved) st.erase(i);
            toBeRemoved.clear();
            prevLevel = level;
        }

        if (word == endWord) {
            ans.push_back(store);
        }

        for (int i = 0; i < word.size(); i++) {
            string original = word;
            for (char c = 'a'; c <= 'z'; c++) {
                word[i] = c;
                if (st.find(word) != st.end()) {
                    auto temp = store;
                    temp.push_back(word);
                    q.push({temp, level+1});
                    toBeRemoved.push_back(word);
                }
            }
            word = original;
        }
    }

    return ans;
}

// Minimum Multiplications to Reach End : 
int minimumMultiplications(vector<int>& arr, int start, int end) {
    // code here
    int maxI = 100000;
    vector<int> vis (maxI, -1);
    vis[start] = 0;
    queue<pair<int, int>> q;
    q.push({start, 0});
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        int src = p.first, level = p.second;
        if (src == end) return level;
        
        for (auto num: arr) {
            int currDest = ((src*num)%maxI);
            if (vis[currDest] == -1) {
                vis[currDest] = vis[src] + 1;
                q.push({currDest, level+1});
            } 
        }
    }
    
    return vis[end];
}

// Find the City With the Smallest Number of Neighbors at a Threshold Distance (Leetcode)
int findTheCity(int n, vector<vector<int>>& edges, int small) {
    vector<vector<pair<int, int>>> graph (n, vector<pair<int, int>> ());
    vector<vector<int>> adjArr (n, vector<int> (n, INT_MAX));

    for (auto arr: edges) {
        adjArr[arr[0]][arr[1]] = arr[2];
        adjArr[arr[1]][arr[0]] = arr[2];
    }

    // Apply Floyd Warshall :
    for (int helper = 0; helper < n; helper++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                if (adjArr[helper][i] == INT_MAX || adjArr[j][helper] == INT_MAX) continue;

                int compDist = adjArr[helper][i] + adjArr[j][helper];
                if (adjArr[i][j] == INT_MAX) {
                    adjArr[i][j] = compDist;
                } else {
                    adjArr[i][j] = min (adjArr[i][j], compDist);
                }

            }
        }
    }

    for (int i = 0; i < n; i++) {
        adjArr[i][i] = 0;
    }

    int minCity = -1, cityCount = INT_MAX;
    for (int src = 0; src < n; src++) {
        int currCount = 0;
        for (int i = 0; i < n; i++) {
            if (adjArr[src][i] <= small) currCount++;
        }
        
        if (currCount <= cityCount) {
            cityCount = currCount;
            minCity = src;
        }
    }

    return minCity;
}