// Vertical Order Traversal (VVVV Imp)
void generate (TreeNode* root, int level, int depth, map<int, map<int, multiset<int>>>& map1) {
    if (root == nullptr) return;
    if (map1.find(level) == map1.end()) {
        multiset<int> ms; ms.insert(root->val);
        map<int, multiset<int>> mp; mp[depth] = ms;
        map1[level] = mp;
    } else {
        if (map1[level].find(depth) == map1[level].end()) {
            multiset<int> ms; ms.insert(root->val);
            map1[level][depth] = ms;
        } else {
            map1[level][depth].insert (root->val);
        }
    }
    generate (root->left, level-1, depth+1, map1);
    generate (root->right, level+1, depth+1, map1);
}
vector<vector<int>> verticalTraversal(TreeNode* root) {
    map<int, map<int, multiset<int>>> mp;
    generate (root, 0, 0, mp);
    vector<vector<int>> ans;
    for (auto i : mp) {
        vector<int> sub;
        for (auto j: i.second) {
            vector<int> miniSub (j.second.begin(), j.second.end());
            sub.insert (sub.end(), miniSub.begin(), miniSub.end());
        }
        ans.push_back(sub);
    }
    return ans;
}

//Maximum Sum of Non Adjacent Nodes in Binary Tree (VVVVV IMP!)
pair<int, int> solve (Node* root) {
    if (root == nullptr) return {0, 0};
    pair<int, int> leftP = solve(root->left);
    pair<int, int> rightP = solve(root->right);
    pair<int, int> p;
    p.first = root->data + leftP.second + rightP.second;
    p.second = max(leftP.first, leftP.second) + max(rightP.first, rightP.second);
    return p;
}

int getMaxSum(Node *root) 
{
    // Add your code here
    pair<int, int> p = solve(root);
    return max(p.first, p.second);
}

//Find Duplicate Subtrees : 
string generate (TreeNode* root, unordered_map<string, pair<TreeNode*, int>>& map) {
    if (root == nullptr) return "";
    string leftStr = generate (root->left, map);
    string rightStr =  generate (root->right, map);
    string str = leftStr + "," + rightStr +","+ to_string(root->val);
    if (map.find(str) == map.end()) {
        map[str] = {root, 1};
    } else {
        map[str].second++;
    }
    return str;
}
vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
    unordered_map<string, pair<TreeNode*, int>> map;
    generate (root, map);
    vector<TreeNode*> arr;
    for (auto i: map) {
        if (i.second.second > 1) {
            arr.push_back (i.second.first);
        }
    }
    return arr;
}

//Morris Inorder Traversal (VVVV Important!) : 
vector<int> inOrder(Node* root) {
    vector<int> inorder;
    while (root != nullptr) {
        if (root->left) {
            Node* temp = root->left;
            while (temp->right != nullptr && temp->right != root) {
                temp = temp->right;
            }
            if (temp->right == nullptr) {
                temp->right = root;
                root = root->left;
            } else {
                temp->right = nullptr;
                inorder.push_back(root->data);
                root = root->right;
            }
        } else {
            inorder.push_back(root->data);
            root = root->right;
        }
    }
    return inorder;
}

// Morris Preorder Traversal (VVVV Important!) :
vector <int> preorder(Node* root)
{
    vector<int> preorder;
    while (root != nullptr) {
        if (root->left) {
            Node* temp = root->left;
            while (temp->right != nullptr && temp->right != root) {
                temp = temp->right;
            }
            if (temp->right == nullptr) {
                temp->right = root;
                preorder.push_back(root->data);
                root = root->left;
            } else {
                temp->right = nullptr;
                root = root->right;
            }
        } else {
            preorder.push_back(root->data);
            root = root->right;
        }
    }
    return preorder;
}

//Morris Postorder Traversal (VVVV Important!) : 
vector <int> postOrder(Node* root)
{
  vector<int> postorder;
  while (root != nullptr) {
      if (root->right) {
          Node* temp = root->right;
          while (temp->left != nullptr && temp->left != root) temp = temp->left;
          if (temp->left == nullptr) {
              temp->left = root;
              postorder.push_back(root->data);
              root = root->right;
          } else {
              temp->left = nullptr;
              root = root->left;
          }
      } else {
          postorder.push_back(root->data);
          root = root->left;
      }
  }
  reverse (postorder.begin(), postorder.end());
  return postorder;
}

//Time taken to Burn Tree From A Certain Point (VVVVV Important!) : 
void lvlOrderTraversal (Node* root, unordered_map<Node*, Node*>& parentMap, int target, Node*& start) {
    queue<Node*> q; q.push(root);
    parentMap[root] = nullptr;
    while (!q.empty()) {
        Node* tempRoot = q.front(); q.pop();
        if (tempRoot->data == target) start = tempRoot;
        if (tempRoot->left) {
            parentMap[tempRoot->left] = tempRoot; q.push(tempRoot->left);
        }
        if (tempRoot->right) {
            parentMap[tempRoot->right] = tempRoot; q.push(tempRoot->right);
        }
    }
}
int minTime(Node* root, int target) 
{
    Node* start = nullptr;
    unordered_map<Node*, Node*> parentMap;
    lvlOrderTraversal (root, parentMap, target, start);
    unordered_map<Node*, bool> visited;
    queue<Node*> q; q.push(start); q.push(nullptr);
    int seconds = 0;
    while (!q.empty()) {
        Node* present = q.front(); q.pop(); 
        if (present) {
            visited[present] = true;
            if (present->left && (visited.find(present->left) == visited.end())) {
                q.push(present->left);
            }
            if (present->right && (visited.find(present->right) == visited.end())) {
                q.push(present->right);
            }
            if (parentMap[present] && (visited.find(parentMap[present]) == visited.end())) {
                q.push(parentMap[present]);
            }
        } else {
            seconds++;
            if (!q.empty()) {
                q.push(nullptr);
            }
        }
    }
    return seconds-1;
}