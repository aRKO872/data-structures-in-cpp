// construct tree from preorder and inorder traversal : 
Node* build (vector<int>& preorder, vector<int>& inorder, int& preInd, int lo, int hi) {
    if (lo > hi || preInd >= preorder.size()) {
        return nullptr;
    }
    int rootElement = preorder[preInd++];
    Node* root = new Node(rootElement);
    int ind = -1;
    for (int i = lo; i <= hi; i++) {
        if (inorder[i] == rootElement) {ind = i; break;}
    }
    root->left = build (preorder, inorder, preInd, lo, ind-1);
    root->right = build (preorder, inorder, preInd, ind+1, hi);
    return root;
}
Node* buildTree(vector<int>& preorder, vector<int>& inorder) {
    int preInd = 0;
    return build (preorder, inorder, preInd, 0, preorder.size()-1);
}

// construct tree from postorder and inorder traversal :
Node* build (vector<int>& inorder, vector<int>& postorder, int& postInd, int lo, int hi) {
    if (lo > hi || postInd < 0) {
        return nullptr;
    }
    int rootElement = postorder[postInd--];
    Node* root = new Node (rootElement);
    int ind = -1;
    for (int i = lo; i <= hi; i++) {
        if (inorder[i] == rootElement) {ind = i; break;}
    }
    root->right = build (inorder, postorder, postInd, ind+1, hi);
    root->left = build (inorder, postorder, postInd, lo, ind-1);
    return root;
}
Node* buildTree(vector<int>& inorder, vector<int>& postorder) {
    int postInd = postorder.size()-1;
    return build (inorder, postorder, postInd, 0, inorder.size()-1);
}

//Construct a Binary tree from preorder and postorder traversal : 
Node* buildTree (vector<int>& preorder, vector<int>& postorder, int& preIndex, int st, int end) {
    if (preIndex >= preorder.size() || st > end) return nullptr;
    Node* root = new Node(preorder[preIndex++]);
    if (st == end) return root;
    int postmid = st;
    for (int i = st; i < end; i++) {
        if (postorder[i] == preorder[preIndex]) {postmid = i; break;}
    }
    root->left = buildTree (preorder, postorder, preIndex, st, postmid);
    root->right = buildTree (preorder, postorder, preIndex, postmid+1, end-1);
    return root;
}
Node* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
    int preIndex = 0;
    return buildTree (preorder, postorder, preIndex, 0, postorder.size()-1);
}

// Top View of Binary Tree : 
vector<int> topView(Node *root)
{
    //Your code here
    queue<pair<Node*, int>> st; map<int, int> map;
    st.push ({root, 0});
    while (!st.empty()) {
        auto popped = st.front(); st.pop();
        int line = popped.second;
        if (map.find(line) == map.end()) {
            map[line] = popped.first->data;
        }
        if (popped.first->left != nullptr) st.push({popped.first->left, line-1});
        if (popped.first->right != nullptr) st.push({popped.first->right, line+1});
    }
    vector<int> ans;
    for (auto i: map) ans.push_back(i.second);
    return ans;
}

//Bottom View of Binary Tree : 
vector <int> bottomView(Node *root) {
    // Your Code Here
    queue<pair<Node*, int>> q;
    q.push({root, 0});
    vector<int> ans;
    map<int, int> map;
    while (!q.empty()) {
        auto popped = q.front(); q.pop();
        Node* node = popped.first;
        int hd = popped.second;
        map[hd] = node->data;
        if (node->left) q.push({node->left, hd-1});
        if (node->right) q.push({node->right, hd+1});
    }
    for (auto i : map) {
        ans.push_back(i.second);
    }
    return ans;
}

//Left View of Binary Tree :
void generate (Node* root, vector<int>& ans, int level, unordered_map<int, int>& map) {
    if (root == nullptr) return;
    if (map.find(level) == map.end()) {
        ans.push_back(root->data);
        map[level] = root->data;
    }
    if (!root->left && !root->right) return;
    generate(root->left, ans, level+1, map);
    generate(root->right, ans, level+1, map);
}

vector<int> leftView(Node *root)
{
   // Your code here
   if (root == nullptr) return {};
   vector<int> ans; unordered_map<int, int> map;
   generate (root, ans, 0, map);
   return ans;
}

// Right View of Binary Tree :
void generate (Node* root, vector<int>& ans, int level, unordered_map<int, int>& map) {
    if (root == nullptr) return;
    if (map.find(level) == map.end()) {
        ans.push_back(root->data);
        map[level] = root->data;
    }
    if (!root->left && !root->right) return;
    generate(root->right, ans, level+1, map);
    generate(root->left, ans, level+1, map);
}
vector<int> rightSideView(Node* root) {
    if (root == nullptr) return {};
    vector<int> ans; unordered_map<int, int> map;
    generate (root, ans, 0, map);
    return ans;
}

//Boundary Traversal of Binary Tree : 
void getLeftView (Node* root, vector<int>& arr) {
    if (root == nullptr) return;
    if (!root->left && !root->right) return;
    arr.push_back(root->data);
    if (root->left) getLeftView (root->left, arr);
    else getLeftView (root->right, arr);
}

void getBottomView (Node* root, vector<int>& arr) {
    if (root == nullptr) return;
    if (!root->left && !root->right) arr.push_back(root->data);
    getBottomView (root->left, arr);
    getBottomView (root->right, arr);
}

void getRightView (Node* root, vector<int>& arr) {
    if (root == nullptr) return;
    if (!root->left && !root->right) return;
    if (root->right) getRightView (root->right, arr);
    else getRightView (root->left, arr);
    arr.push_back(root->data);
}

vector <int> boundary(Node *root)
{
    //Your code here
    vector<int> arr;
    arr.push_back(root->data);
    getLeftView (root->left, arr);
    if (root->left || root->right) getBottomView (root, arr);
    getRightView (root->right, arr);
    return arr;
}

// Zigzag Traversal of Binary Tree : 
vector<vector<int>> zigzagLevelOrder(Node* root) {
    vector<vector<int>> ans;
    if (root == nullptr) return ans;
    queue<Node*> q; q.push(root); q.push(nullptr);
    vector<int> sub;
    int dec = 0;
    while (!q.empty()) {
        Node* popped = q.front(); q.pop();
        if (popped != nullptr) {
            sub.push_back(popped->data);
            if (popped->right) q.push(popped->right);
            if (popped->left) q.push(popped->left);
        } else {
            if (dec%2 == 0) reverse(sub.begin(), sub.end());
            ans.push_back(sub);
            dec++;
            sub.clear();
            if (!q.empty()) q.push(nullptr);
        }
    }
    return ans;
}

//Diagonal Traversal Of Binary Tree : 
vector<int> diagonal(Node *root)
{
   // your code here
   queue<Node*> q; q.push(root);
   vector<int> arr;
   while (!q.empty()) {
       Node* popped = q.front(); q.pop();
       while (popped) {
           arr.push_back(popped->data);
           if (popped->left) q.push(popped->left);
           popped = popped->right;
       }
   }
   return arr;
}

//Flatten Binary Tree To Linked List : 
void flatten(Node* root) {
    if (root == nullptr) return;
    stack<Node*> st;
    st.push(root);
    while (!st.empty()) {
        Node* popped = st.top(); st.pop();
        if (popped->right) st.push(popped->right);
        if (popped->left) st.push(popped->left);
        if (!st.empty()) {
            popped->left = nullptr;
            popped->right = st.top();
        }
    }
}

// Cousins in a Binary Tree :
int heightX, heightY, parentX, parentY;
void find (TreeNode* root, int x, int y, int parX, int parY, int level) {
    if (!root) return;
    if (root->val == x) {heightX = level; parentX = parX;}
    if (root->val == y) {heightY = level; parentY = parY;} 
    find (root->left, x, y, root->val, root->val, level+1);
    find (root->right, x, y, root->val, root->val, level+1);
}
bool isCousins(TreeNode* root, int x, int y) {
    find(root, x, y, 0, 0, 0);
    return (heightX == heightY && parentX != parentY);
}