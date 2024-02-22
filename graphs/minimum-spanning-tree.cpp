// Prim's Algorithm : 
int findLowest (vector<int>& key, vector<int>& mst) {
  int lowInd = -1;
  int low = INT_MAX;
  for (int i = 0; i < key.size(); i++) {
      if (mst[i] == 0 && key[i] < low) {
          low = key[i]; lowInd = i;
      }
  }
  
  return lowInd;
}

int spanningTree(int V, vector<vector<int>> adj[])
{
    // code here
    vector<int> key (V, INT_MAX);
    vector<int> mst (V);
    key[0] = 0;
    
    while (true) {
        int u = findLowest (key, mst);
        if (u == -1) break;
        mst[u] = 1;
        
        for (auto arr: adj[u]) {
            int v = arr[0], wt = arr[1];
            if (mst[v] == 0 && wt < key[v]) {
                key[v] = wt;
            }
        }
    }
    
    int count = 0;
    for (auto i: key) count += i;
    
    return count;
}