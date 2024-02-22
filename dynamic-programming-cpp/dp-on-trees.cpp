// House Robber 3 :
int recSol (TreeNode* root, unordered_map<TreeNode*, int>& map) {
    if (!root) return 0;
    if (map.find(root) != map.end()) return map[root];

    int take = root->val;
    if (root->left) take += (recSol (root->left->left, map) + recSol (root->left->right, map)); 
    if (root->right) take += (recSol (root->right->right, map) + recSol (root->right->left, map));
    int notTake = recSol (root->left, map) + recSol (root->right, map);
    return map[root] = max (take, notTake);
}
int rob(TreeNode* root) {
    unordered_map<TreeNode*, int> map;
    return recSol (root, map);
}

// Unique Binary Search Trees 1 : 
int recSol (int n, vector<int>& dp) {
    if (dp[n] != -1) return dp[n];

    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += (recSol (i-1, dp) * recSol (n-i, dp));
    }

    return dp[n] = sum;
}

int bottomUp (int n) {
    vector<int> dp (n+1, 0);
    dp[1] = 1; dp[0] = 1;

    for (int i = 2; i <= n; i++) {
        int sum = 0;
        for (int j = 1; j <= i; j++) {
            sum += (dp[j-1] * dp[i-j]);
        }
        dp[i] = sum;
    }

    return dp[n];
}

int numTrees(int n) {
    if (n == 1 || n == 0) return 1;
    vector<int> dp (n+1, -1);
    // dp[1] = 1; dp[0] = 1;
    // return recSol (n, dp);
    return bottomUp (n);
} 

// Unique Binary Search Trees 2 :
vector<TreeNode*> generateAllBST (int st, int end, map<pair<int, int>, vector<TreeNode*>>& map) {
    if (st > end) return {nullptr};
    if (map.find({st, end}) != map.end()) return map[{st, end}];

    vector<TreeNode*> ans; 
    for (int i = st; i <= end; i++) {
        vector<TreeNode*> left = generateAllBST (st, i-1, map);
        vector<TreeNode*> right = generateAllBST (i+1, end, map);
        
        for (int j = 0; j < left.size(); j++) {
            for (int k = 0; k < right.size(); k++) {
                TreeNode* root = new TreeNode (i);
                root->left = left[j];
                root->right = right[k];
                ans.push_back(root);
            }
        }
    }

    return map[{st, end}] = ans;
}
vector<TreeNode*> generateTrees(int n) {
    map<pair<int, int>, vector<TreeNode*>> map;
    return generateAllBST (1, n, map);
}