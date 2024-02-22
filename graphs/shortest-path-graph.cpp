// Shortest Path in Unweighted Undirected Graph (Using BFS) :
int findShortest (vector<vector<int>>& graph, vector<int>& visited, int src, int dest) {
    int count = 0;
    queue<pair<int, int>> q; 
    q.push({src, 0}); visited[src]++;
    bool notFound = true;
    
    while (!q.empty()) {
        auto poppedEle = q.front(); q.pop();
        int popped = poppedEle.first;
        count = poppedEle.second;
        if (popped == dest) {
            notFound = false;
            break;
        }
        
        for (int nbr : graph[popped]) {
            if (visited[nbr] == 0) {
                visited[nbr] = 1;
                q.push ({nbr, count+1});
            }
        }
    }
    
    if (notFound == true) return -1;
    return count;
}

// Shortest Path In Unweighted Graph (Using DFS) :
int findShortest (vector<vector<int>>& graph, vector<int>& visited, int src, int dest) {
    if (src == dest) return 0;
    
    visited[src] = 1;
    int shortest = INT_MAX;
    
    for (int nbr: graph[src]) {
        if (visited[nbr] == 0) {
            int curr = findShortest (graph, visited, nbr, dest);
            if (curr != INT_MAX) {
                shortest = min (shortest, 1 + curr);
            }
        }
    }
    
    visited[src] = 0;
    return shortest;
}

// Print Shortest Path in Unweighted Undirected Graph : 
vector<int> shortestPath( vector<pair<int,int>> edges , int n , int s , int t){
	
	// Write your code here
	vector<int> parent (n+1, -1);
	vector<int> vis (n+1, 0);

	vector<vector<int>> graph (n+1, vector<int> ());
	for (auto p: edges) {
		graph[p.first].push_back(p.second);
		graph[p.second].push_back(p.first);
	}

	queue<int> q;
	vis[s] = 1;
	parent[s] = -1;
	q.push(s);

	while (!q.empty()) {
		int node = q.front(); q.pop();
		for (auto nbr: graph[node]) {
			if (vis[nbr] == 0) {
				vis[nbr] = 1;
				parent[nbr] = node;
				q.push(nbr);
			}
		}
	}
	vector<int> ans;

	while (t != -1) {
		ans.push_back(t);
		t = parent[t];
	}
	reverse (ans.begin(), ans.end());
	return ans;
}

// Print Shortest Path in Weighted DAG (using DFS) : 
int recSol (vector<vector<pair<int, int>>>& edges, vector<int>& vis, int src, int dest) {
    if (src == dest) return 0;
    vis[src] = 1;
    int minDist = INT_MAX;
    
    for (auto p: edges[src]) {
        int nbr = p.first;
        int wt = p.second;
        
        if (vis[nbr] == 0) {
            int nbrDist = recSol (edges, vis, nbr, dest);
            if (nbrDist != INT_MAX) {
                minDist = min (minDist, wt + nbrDist);
            }
        }
    }
    
    vis[src] = 0;
    return minDist;
}
vector<int> shortestPath(int N,int M, vector<vector<int>>& edges){
  // code here
  vector<vector<pair<int, int>>> graph (N, vector<pair<int, int>> ());
  
  for (auto arr: edges) {
      graph[arr[0]].push_back({arr[1], arr[2]});
  }
  
  vector<int> ans;
  for (int i = 0; i < N; i++) {
      vector<int> vis (N, 0);
      int dist = recSol (graph, vis, 0, i);
      int newDist = (dist == INT_MAX) ? -1 : dist;
      ans.push_back(newDist);
  }
  return ans;
}

// Print Shortest Path in Weighted DAG (Optimized DFS) : 
void findTopo (vector<vector<pair<int, int>>>& graph, stack<int>& st, vector<int>& vis, int src) {
    vis[src] = 1;
    
    for (auto p: graph[src]) {
        if (vis[p.first] == 0) {
            findTopo (graph, st, vis, p.first);
        }
    }
    
    st.push(src);
}

vector<int> shortestPath(int N,int M, vector<vector<int>>& edges){
    stack<int> st;
    vector<vector<pair<int, int>>> graph (N, vector<pair<int, int>> ());
    vector<int> vis (N, 0);
    for (auto arr: edges) {
        graph[arr[0]].push_back({arr[1], arr[2]});
    }
    
    findTopo (graph, st, vis, 0);
    vector<int> distance (N, INT_MAX);
    int topEle = st.top(); st.pop();
    distance[topEle] = 0;
    
    for (auto nbr: graph[topEle]) {
        if (distance[topEle] + nbr.second < distance[nbr.first]) {
            distance[nbr.first] = distance[topEle] + nbr.second;
        }
    }
    
    while (!st.empty()) {
        int topEle = st.top(); st.pop();
        
        if (distance[topEle] != INT_MAX) {
            for (auto nbr: graph[topEle]) {
                if (distance[topEle] + nbr.second < distance[nbr.first]) {
                    distance[nbr.first] = distance[topEle] + nbr.second;
                }
            }
        }
    }
    
    for (int i = 0; i < N; i++) distance[i] = (distance[i] == INT_MAX) ? -1 : distance[i];
    return distance;
}

//Dijkstra Shortest Path Distance from source to all nodes : 
vector<int> dijkstra(vector<vector<int>> &vec, int vertices, int edges, int source) {
    // Write your code here.
    vector<vector<pair<int, int>>> graph (vertices, vector<pair<int, int>> ());

    for (auto arr : vec) {
      graph[arr[0]].push_back({arr[1], arr[2]});
      graph[arr[1]].push_back({arr[0], arr[2]});
    }

    vector<int> distance (vertices, INT_MAX);
    set<pair<int, int>> st;

    distance[source] = 0;
    for (auto nbr : graph[0]) {
      if (distance[source] + nbr.second < distance[nbr.first]) {
          distance[nbr.first] = nbr.second;
          st.insert({nbr.second, nbr.first});
      }
    }

    while (!st.empty()) {
        auto p = *st.begin(); st.erase(st.begin());
        int src = p.second;

        for (auto nbr : graph[src]) {
            if (distance[src] != INT_MAX && distance[src] + nbr.second < distance[nbr.first]) {
                distance[nbr.first] = nbr.second + distance[src];
                st.insert({nbr.second, nbr.first});
            }
        }
    }

    return distance;
}

// Dijkstra Algo to Print Shortest Path In Undirected Weighted Graph : 
vector<int> shortestPath(int n, int m, vector<vector<int>>& edges) {
    // Code here
    vector<vector<pair<int, int>>> graph (n+1, vector<pair<int, int>> ());
    
    for (auto arr: edges) {
        graph[arr[0]].push_back({arr[1], arr[2]});
        graph[arr[1]].push_back({arr[0], arr[2]});
    }
    
    vector<int> parent (n+1, -1);
    vector<int> distance (n+1, INT_MAX);
    distance[1] = 0;
    priority_queue<pair<int, int> , vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 1});
    
    while (!pq.empty()) {
        auto p = pq.top(); pq.pop();
        int src = p.second;
        
        for (auto nbr: graph[src]) {
            int wt = nbr.second;
            if (distance[src] != INT_MAX && distance[src] + wt < distance[nbr.first]) {
                distance[nbr.first] = distance[src] + wt;
                parent[nbr.first] = src;
                pq.push({wt, nbr.first});
            }
        }
    }
    
    if (distance[n] == INT_MAX) return {-1};
    
    vector<int> ans;
    while (n != -1) {
        ans.push_back(n);
        n = parent[n];
    }
    
    reverse (ans.begin(), ans.end());
    return ans;
}

// Bellman Ford Algo for Shortest Path in Directed Graph having negative weights:
vector<int> bellman_ford(int V, vector<vector<int>>& adj, int S) {
    // Code here
    int maxI = pow (10, 8);
    vector<int> distance (V, maxI);
    
    distance[S] = 0;
    
    for (int pass = 0; pass < V-1; pass++) {
        for (auto arr: adj) {
            if (distance[arr[0]] != maxI && distance[arr[0]] + arr[2] < distance[arr[1]]) {
                distance[arr[1]] = distance[arr[0]] + arr[2];
            }
        }
    }
    
    for (auto arr: adj) {
        if (distance[arr[0]] != maxI && distance[arr[0]] + arr[2] < distance[arr[1]]) {
            return {-1};
        }
    }
    
    return distance;
}

// Floyd Warshall (Shortest Path from all sources to all destinations) :
void shortest_distance(vector<vector<int>>&matrix){
    // Code here
    int v=matrix.size();
    for(int k=0;k<v;k++){ //vertex as intermediate 
        for(int i=0;i<v;i++){ //all vertex as source one by one
            for(int j=0;j<v;j++){ //destination 
            if(matrix[i][k]==-1 || matrix[k][j]==-1){
                continue;
            }
            int cur=matrix[i][k]+matrix[k][j];
            
            if(matrix[i][j]==-1) matrix[i][j]=cur;
            else matrix[i][j]=min(matrix[i][j],cur);
            }
        }
    }
}