// Topological Sort in DAG using DFS : 
void recSol (vector<int> adj[], vector<int>& visited, vector<int>& ans, int ind) {
    visited[ind] = 1;
    
    for (auto nbr: adj[ind]) {
        if (visited[nbr] == 0) {
            recSol (adj, visited, ans, nbr);
        }
    }
    
    ans.push_back(ind);
}
vector<int> topoSort(int V, vector<int> adj[]) 
{
    // code here
    vector<int> visited (V, 0);
    vector<int> ans;
    for (int i = 0; i < V; i++) {
        if (visited[i] == 0) {
            recSol (adj, visited, ans, i);
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

// Topological Sort Using BFS (Kahn's Algo) : 
vector<int> topoSort(int V, vector<int> adj[]) {
  // code here
  unordered_map<int, int> indegree;
  for (int i = 0; i < V; i++) {
      for (int nbr: adj[i]) {
          indegree[nbr]++;
      }
  }
  
  queue<int> q;
  for (int i = 0; i < V; i++) {
      if (indegree[i] == 0) {
          q.push(i);
      }
  }
  
  vector<int> ans;
  while (!q.empty()) {
      int popped = q.front(); q.pop();
      for (auto nbr: adj[popped]) {
          indegree[nbr]--;
          if (indegree[nbr] == 0) {
              q.push(nbr);
          }
      }
      ans.push_back(popped);
  }
  
  return ans;
}

// Detect Cycle in Directed Graph Using BFS (Kahn's Algo) :
bool isCyclic(int V, vector<int> adj[]) {
  // code here
  unordered_map<int, int> indegree;
  for (int i = 0; i < V; i++) {
      for (int nbr: adj[i]) {
          indegree[nbr]++;
      }
  }
  
  queue<int> q;
  for (int i = 0; i < V; i++) {
      if (indegree[i] == 0) {
          q.push(i);
      }
  }
  
  vector<int> ans;
  while (!q.empty()) {
      int popped = q.front(); q.pop();
      for (auto nbr: adj[popped]) {
          indegree[nbr]--;
          if (indegree[nbr] == 0) {
              q.push(nbr);
          }
      }
      ans.push_back(popped);
  }
  
  return (ans.size() != V);
}