// Number OF Provinces (Leetcode) : 
int findCircleNum(vector<vector<int>>& g) {
    int count = 0;
    vector<int> vis (g.size(), 0);

    for (int i = 0; i < g.size(); i++) {
      int node = i;
      
      if (vis[node] == 0) {
        count++;
        vis[node] = 1;
        queue<int> q; q.push(node);

        while (!q.empty()) {
          int topEle = q.front(); q.pop();

          for (int nbr = 0; nbr < g[0].size(); nbr++) {
            if (g[topEle][nbr] == 1 && nbr != topEle && vis[nbr] == 0) {
              vis[nbr] = 1;
              q.push(nbr);
            }
          }
        }
      }
    }

    return count;
}

// Flood Fill (Leetcode) :
void dfs (vector<vector<int>>& image, int i, int j, int color) {
    if (image[i][j] == color) return;
    int prev = image[i][j];
    image[i][j] = color;

    if (i-1 >= 0 && image[i-1][j] == prev) dfs (image, i-1, j, color);
    if (j-1 >= 0 && image[i][j-1] == prev) dfs (image, i, j-1, color);
    if (i+1 < image.size() && image[i+1][j] == prev) dfs (image, i+1, j, color);
    if (j+1 < image[0].size() && image[i][j+1] == prev) dfs (image, i, j+1, color);
}
vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
    dfs (image, sr, sc, color);
    return image;
}

// Course Schedule (Leetcode) :
bool canFinish(int n, vector<vector<int>>& edges) {
    vector<vector<int>> graph (n, vector<int> ());

    for (auto arr: edges) {
        graph[arr[1]].push_back(arr[0]);
    }

    vector<int> indegree (n, 0);
    for (auto edges: graph) {
        for (auto nbr: edges) {
            indegree[nbr]++;
        }
    }

    queue<int> q;

    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    vector<int> topo;

    while (!q.empty()) {
        int topEle = q.front(); q.pop();
        topo.push_back(topEle);

        for (auto nbr: graph[topEle]) {
            indegree[nbr]--;
            if (indegree[nbr] == 0) q.push(nbr);
        }
    }

    return topo.size() == n;
}

// Word Ladder 1 :
int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> st (wordList.begin(), wordList.end());
    queue<pair<string, int>> q;

    q.push({beginWord, 1});
    st.erase(beginWord);

    while (!q.empty()) {
        auto p = q.front(); q.pop();
        string poppedWord = p.first; 
        int currCount = p.second;

        if (poppedWord == endWord) return currCount;
        for (int i = 0; i < poppedWord.size(); i++) {
            string tempWord = poppedWord;
            for (char ch = 'a'; ch <= 'z'; ch++) {
                tempWord[i] = ch;
                if (st.find(tempWord) != st.end()) {
                    st.erase(tempWord);
                    q.push({tempWord, currCount+1});
                }
            }
        }
    }

    return 0;
}

// Minimum Effort Path (Leetcode) :
int minimumEffortPath(vector<vector<int>>& heights) {
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    vector<vector<int>> distance (heights.size(), vector<int> (heights[0].size(), INT_MAX));

    distance[0][0] = 0;
    pq.push({0, {0, 0}});

    while (!pq.empty()) {
        auto p = pq.top(); pq.pop();

        int dist = p.first;
        int i = p.second.first, j = p.second.second;
        
        if (i-1 >= 0) {
            int currDist = max (dist, abs (heights[i-1][j]-heights[i][j]));
            if (currDist < distance[i-1][j]) {
                distance[i-1][j] = currDist;
                pq.push({currDist, {i-1, j}});
            }
        }

        if (j-1 >= 0) {
            int currDist = max (dist, abs (heights[i][j-1]-heights[i][j]));
            if (currDist < distance[i][j-1]) {
                distance[i][j-1] = currDist;
                pq.push({currDist, {i, j-1}});
            }
        }

        if (i+1 < heights.size()) {
            int currDist = max (dist, abs (heights[i+1][j]-heights[i][j]));
            if (currDist < distance[i+1][j]) {
                distance[i+1][j] = currDist;
                pq.push({currDist, {i+1, j}});
            }
        }

        if (j+1 < heights[0].size()) {
            int currDist = max (dist, abs (heights[i][j+1]-heights[i][j]));
            if (currDist < distance[i][j+1]) {
                distance[i][j+1] = currDist;
                pq.push({currDist, {i, j+1}});
            }
        }
    }

    return distance[heights.size()-1][heights[0].size()-1];
}