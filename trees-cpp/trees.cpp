class TreeNode {
  public: 
  int data; TreeNode* left; TreeNode* right;
  TreeNode(int val) {
    data = val;
    left = nullptr;
    right = nullptr;
  }
};

//Building a binary Tree:
TreeNode* buildTree () {
  int data;
  cin >> data;
  if (data == -1) return nullptr;
  TreeNode* root = new TreeNode(data);
  root->left = buildTree ();
  root->right = buildTree ();
  return root;
}

//build tree from level order traversal : 
Node* insert (int data, Node* root, queue<Node*>& q) {
    Node* newNode = new Node(data);
    if (root == nullptr) {
        root = newNode;
    } else if (q.front()->left == nullptr) {
        q.front()->left = newNode;
    } else {
        q.front()->right = newNode; q.pop();
    }
    q.push(newNode);
    return root;
}

void inorder (TreeNode* root) {
  if (root != nullptr) {
    inorder (root->left);
    cout << root->data << " ";
    inorder (root->right);
  }
}

void preorder (TreeNode* root) {
  if (root != nullptr) {
    cout << root->data << " ";
    preorder (root->left);
    preorder (root->right);
  }
}

void postorder (TreeNode* root) {
  if (root != nullptr) {
    postorder (root->left);
    postorder (root->right);
    cout << root->data << " ";
  }
}

// Level Order Traversal (VVVV Important!) : 
vector<int> levelOrder(Node* node)
{
  //Your code here
  queue<Node*> q;
  q.push(node);
  vector<int> ans;
  while (!q.empty()) {
      Node* tree = q.front(); q.pop();
      ans.push_back(tree->data);
      if (tree->left != nullptr) q.push(tree->left); 
      if (tree->right != nullptr) q.push(tree->right); 
  }
  return ans;
}

//Level Order Traversal, but store each level in 2D array, DFS Approach : 
void levelRec (vector<vector<int>>& ans, TreeNode* root, int level) {
    if (root == nullptr) return;
    if (ans.size() == level) ans.push_back(vector<int>());
    ans[level].push_back(root->data);
    levelRec (ans, root->left, level+1);
    levelRec (ans, root->right, level+1);
}
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> ans; 
    levelRec (ans, root, 0);
    return ans;
}

//Level Order Traversal, but store each level in 2D array, BFS Approach using Queue:
vector<vector<int>> levelOrder(TreeNode* root) {
    if (root == nullptr) return vector<vector<int>>();
    queue<TreeNode*> q;
    q.push(root);
    q.push(nullptr);
    vector<vector<int>> ans;
    vector<int> sub;
    while (!q.empty()) {
        TreeNode* node = q.front();
        if (node == nullptr) {
            ans.push_back(sub); q.pop();
            sub = vector<int>();
            if (!q.empty()) {
                q.push(nullptr);
            }
        } else {
            sub.push_back(node->data);
            q.pop();
            if (node->left != nullptr) q.push(node->left);
            if (node->right != nullptr) q.push(node->right);
        }
    }
    return ans;
}

//Diameter of Binary Tree : 
int height (TreeNode* root) {
    if (root == nullptr) return 0;
    int leftHeight = height (root->left)+1;
    int rightHeight = height (root->right)+1;
    return max(leftHeight, rightHeight);
}
int diameterOfBinaryTree(TreeNode* root) {
    if (root == nullptr) return 0;
    int leftDiameter = diameterOfBinaryTree (root->left);
    int rightDiameter = diameterOfBinaryTree (root->right);
    int leftLen = height (root->left);
    int rightLen = height (root->right);
    int sum = leftLen + rightLen;
    return max(sum, max(leftDiameter, rightDiameter));
}

//Faster way to find diameter of Binary Tree : 
int D = 0;
int height (TreeNode* root) {
    if (root == nullptr) return 0;
    int leftHt = height(root->left);
    int rightHt = height(root->right);
    D = max(D, leftHt+rightHt);
    return max(leftHt, rightHt) + 1;
}
int diameterOfBinaryTree(TreeNode* root) {
    height (root);
    return D;
}

// Check if Tree is Balanced or Not : 
bool isBalanced(TreeNode* root) {
    if (root == nullptr) return true;
    int leftHt = height (root->left);
    int rightHt = height (root->right);
    bool isBalance = (abs(leftHt - rightHt) <= 1);
    bool isLeftBalanced = isBalanced (root->left);
    bool isRightBalanced = isBalanced (root->right);
    return (isLeftBalanced && isRightBalanced && isBalance);
}

//Fast Way to Find if Tree is Balanced or not : 
bool check = true;
int height (TreeNode* root) {
    if (root == nullptr) return 0;
    int leftHt = height (root->left);
    int rightHt = height (root->right);
    if (leftHt != rightHt && abs(leftHt-rightHt) > 1) check = false;
    return max (leftHt, rightHt) + 1;
} 
bool isBalanced(TreeNode* root) {
    height (root);
    return check;
}

//Check if Two given trees are same or not :
bool isSameTree(TreeNode* p, TreeNode* q) {
    if ((p == nullptr && q != nullptr) || (p != nullptr && q == nullptr)) return false;
    if (p == nullptr && q == nullptr) return true;
    if (p->data != q->data) return false;
    bool leftTrue = isSameTree (p->left, q->left);
    bool rightTrue = isSameTree (p->right, q->right);
    return leftTrue && rightTrue;
}

// Check if Trees are mirror of each other : 
bool isMirror (TreeNode* p, TreeNode* q) {
    if (p == nullptr && q == nullptr) return true;
    if ((p != nullptr && q == nullptr) || (p == nullptr && q != nullptr)) return false;
    if (p->data != q->data) return false;
    bool checkLeftMirror = isMirror (p->left, q->right);
    bool checkRightMirror = isMirror (p->right, q->left);
    return checkLeftMirror && checkRightMirror;
}

//Iterative Preorder Traversal : 
vector<int> preOrder(Node* node) {
    // code here
    if (node == nullptr) return {};
    stack<Node*> st;
    vector<int> arr;
    st.push(node);
    while (!st.empty()) {
        Node* root = st.top(); st.pop();
        arr.push_back(root->data);
        if (root->right != nullptr) st.push(root->right);
        if (root->left != nullptr) st.push(root->left);
    }
    return arr;
}

//Iterative Postorder Traversal : 
vector<int> postOrder(Node* node) {
    // code here
    if (node == nullptr) return {};
    stack<Node*> st;
    vector<int> arr;
    while (node != nullptr || !st.empty()) {
        if (node != nullptr) {
            st.push(node);
            arr.push_back(node->data);
            node = node->right;
        } else {
            Node* p = st.top(); st.pop();
            node = p->left;
        }
    }
    reverse(arr.begin(), arr.end());
    return arr;
}

// Iterative Inorder Traversal : 
vector<int> inorderTraversal(TreeNode* root) {
    if (root == nullptr) return {};
    stack<TreeNode*> st; vector<int> arr;
    while (root != nullptr || !st.empty()) {
        while (root != nullptr) {
            st.push(root); 
            root = root->left;
        }
        TreeNode* p = st.top(); st.pop();
        arr.push_back(p->val);
        root = p->right;
    }
    return arr;
}

// Is Sum Tree (VVV Imp)
int sum (Node* root) {
    if (root == nullptr) return 0;
    int total = root->data;
    if (root->left != nullptr) total += sum(root->left);
    if (root->right != nullptr) total += sum(root->right);
    return total;
}
bool isSumTree(Node* root)
{
      // Your code here
      if (root == nullptr) return true;
      if (root->left == nullptr && root->right == nullptr) return true;
      bool currIsTrue = ((sum(root->left) + sum(root->right)) == root->data);
      bool leftIsTrue = isSumTree(root->left);
      bool rightIsTrue = isSumTree(root->right);
      return currIsTrue && leftIsTrue && rightIsTrue;
}

//Transform into Sum Tree : 
int sum (Node *root) {
    if (root == nullptr) return 0;
    int total = root->data;
    if (root->left != nullptr) total += sum (root->left);
    if (root->right != nullptr) total += sum (root->right);
    return total;
}
void toSumTree(Node *node)
{
    // Your code here
    if (node == nullptr) return;
    int total = 0;
    total += sum (node->left);
    total += sum (node->right);
    node->data = total;
    toSumTree (node->left);
    toSumTree (node->right);
}

// Lowest Common Ancestor (Most Important!!!) 
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr) return nullptr;
    if (root == p || root == q) return root;
    TreeNode* leftSearch = lowestCommonAncestor (root->left, p, q);
    TreeNode* rightSearch = lowestCommonAncestor (root->right, p, q);
    if (leftSearch != nullptr && rightSearch != nullptr) return root;
    if (leftSearch != nullptr) return leftSearch;
    if (rightSearch != nullptr) return rightSearch;
    return nullptr;
}

//Kth Ancestor In a Tree (VVVV Important!) : 
bool findK (Node *root, int& k, int node, int& ans) {
    if (root == nullptr) return false;
    if (k == 0) return true;
    if (root->data == node) return true;
    bool leftFind = findK (root->left, k, node, ans);
    bool rightFind = findK (root->right, k, node, ans);
    if (leftFind || rightFind) {
        k--;
    }
    if (k == 0) {
        ans = root->data;
    }
    return (leftFind || rightFind);
}

int kthAncestor(Node *root, int k, int node)
{
    int ans = -1;
    findK (root, k, node, ans);
    return ans;
}

// Path Sum (VVVVVV Important) :
bool recSol (TreeNode* root, int targetSum) {
    if (root == nullptr) return (targetSum == 0);
    if (root->left == nullptr && root->right == nullptr) return (root->val == targetSum);
    bool leftCheck = hasPathSum(root->left, targetSum - root->val);
    bool rightCheck = hasPathSum(root->right, targetSum - root->val);
    return leftCheck || rightCheck;
}
bool hasPathSum(TreeNode* root, int targetSum) {
    if (root == nullptr) return false;
    else return recSol (root, targetSum);
}

// Path Sum II (VVVVVV Important) :
void generatePaths (TreeNode* root, int targetSum, vector<vector<int>>& ans, vector<int>& path) {
    if (root == nullptr) return;  
    if (root->left == nullptr && root->right == nullptr) {
        if (targetSum == root->val) {
            path.push_back(root->val);
            ans.push_back(path);
            path.pop_back();
        }
        return;
    }
    path.push_back(root->val);
    generatePaths(root->left, targetSum-root->val, ans, path);
    generatePaths(root->right, targetSum-root->val, ans, path);
    path.pop_back();
}
vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
    vector<vector<int>> ans;
    if (root == nullptr) return ans;
    vector<int> path;
    generatePaths (root, targetSum, ans, path);
    return ans;
}

// Path Sum III (Super VVVVVV Important): 
int noOfPaths (TreeNode* root, long long int targetSum) {
    if (root == nullptr) return 0;
    int count = 0;
    if (((long long int)targetSum-(long long int)root->val) == 0) {
        count = 1;
    } 
    count += noOfPaths (root->left, targetSum - root->val);
    count += noOfPaths (root->right, targetSum - root->val);
    return count;
}
int pathSum(TreeNode* root, int targetSum) {
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr && root->val == targetSum) return 1;
    int pathLeft = pathSum (root->left, targetSum);
    int pathRight = pathSum (root->right, targetSum);
    int currSum = noOfPaths (root, targetSum);
    return currSum + pathLeft + pathRight;
}

// Sum Of Longest BloodLine in a Tree (Important) : 
void bloodLine (Node* root, vector<pair<int, int>>& arr, int depth, int freq) {
    if (root == nullptr) return;
    if (root->left == nullptr && root->right == nullptr) {
        arr.push_back({depth+1, freq+root->data});
        return;
    }
    bloodLine (root->left, arr, depth+1, freq+root->data);
    bloodLine (root->right, arr, depth+1, freq+root->data);
}
int sumOfLongRootToLeafPath(Node *root)
{
    //code here
    if (root == nullptr) return 0;
    vector<pair<int, int>> arr;
    bloodLine (root, arr, 0, 0);
    sort (arr.begin(), arr.end(), [](pair<int, int>& p1, pair<int, int>& p2) {
        if (p1.first == p2.first) return p1.second > p2.second;
        else return p1.first > p2.first;
    });
    return arr[0].second;
}

//Find all ancestors : 
bool generate (struct Node *root, int target, vector<int>& arr) {
    if (root == nullptr) return false;
    if (root->data == target) {
        return true;
    }
    bool leftAns = generate (root->left, target, arr);
    bool rightAns = generate (root->right, target, arr);
    if (leftAns || rightAns) {
        arr.push_back(root->data);
    }
}
vector<int> Ancestors(struct Node *root, int target)
{
        // Code here
        vector<int> arr;
        generate (root, target, arr);
        return arr;
}