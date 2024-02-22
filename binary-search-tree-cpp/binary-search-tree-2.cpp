// Largest BST in a Binary Tree
class NodeData {
    public:
    int size, minVal, maxVal;
    bool isValid;
    NodeData() {
    }
    NodeData(int size, int minVal, int maxVal, bool isValid) {
        this->size = size; this->minVal = minVal; this->maxVal = maxVal; this->isValid = isValid;
    }
};

NodeData* recSolve (Node* root, int& ans) {
    if (!root) return new NodeData (0, INT_MAX, INT_MIN, true);
    NodeData* leftAns = recSolve (root->left, ans);
    NodeData* rightAns = recSolve (root->right, ans);
    
    NodeData* currNodeAns = new NodeData();
    currNodeAns->size = leftAns->size + rightAns->size + 1;
    currNodeAns->minVal = min (root->data, leftAns->minVal);
    currNodeAns->maxVal = max (root->data, rightAns->maxVal);
    if (leftAns->isValid && rightAns->isValid && (leftAns->maxVal < root->data && rightAns->minVal > root->data)) {
        currNodeAns->isValid = true;
    } else {
        currNodeAns->isValid = false;
    }
    
    if (currNodeAns->isValid) ans = max (ans, currNodeAns->size);
    return currNodeAns;
}

int largestBst(Node *root)
{
  //Your code here
  int changeAns = 0;
  recSolve (root, changeAns);
  return changeAns;
}

// Construct Binary Search Tree from it's preorder traversal : 
TreeNode* recSolve (vector<int>& preorder, int& preIndex, int lowBound, int upBound) {
    if (preIndex >= preorder.size()) return nullptr;
    TreeNode* root = nullptr;
    if (preorder[preIndex] > lowBound && preorder[preIndex] < upBound) {
        int element = preorder[preIndex++];
        root = new TreeNode(element);
        root->left = recSolve (preorder, preIndex, lowBound, element);
        root->right = recSolve (preorder, preIndex, element, upBound);
        return root;
    }
    return root;
}
TreeNode* bstFromPreorder(vector<int>& preorder) {
    int preIndex = 0;
    TreeNode* ans = recSolve (preorder, preIndex, INT_MIN, INT_MAX);
    return ans;
}

//Generate BST from it's postorder traversal :
Node* generate (int post[], int& ind, int minVal, int maxVal) {
    if (ind < 0) return nullptr;
    if (post[ind] <= minVal || post[ind] >= maxVal) return nullptr;
    Node* root = new Node (post[ind--]);
    root->right = generate (post, ind, root->data, maxVal);
    root->left = generate (post, ind, minVal, root->data);
    return root;
}

Node *constructTree (int post[], int size)
{
//code here
    int minVal = INT_MIN, maxVal = INT_MAX, ind = size-1;
    return generate (post, ind, minVal, maxVal);
}

// Count number of Pairs amounting to target in the 2 provided BSTs : 
void inorder (Node* root, vector<int>& arr) {
    if (root) {
        inorder (root->left, arr);
        arr.push_back (root->data);
        inorder (root->right, arr);
    }
}
int countPairs(Node* root1, Node* root2, int x)
{
    vector<int> arr1; vector<int> arr2;
    inorder(root1, arr1); inorder(root2, arr2);
    reverse (arr2.begin(), arr2.end());
    int i1 = 0, i2 = 0, noOfPairs = 0;
    while (i1 < arr1.size() && i2 < arr2.size()) {
        if (arr1[i1] + arr2[i2] == x) {i1++; i2++; noOfPairs++;}
        else if (arr1[i1]+arr2[i2] > x) i2++;
        else i1++;
    }
    return noOfPairs;
}

// Find Median of Nodes (Using proper morris traversal) : 
int countOfNodes (Node* root) {
    int count = 0; Node* curr = root;
    while (curr) {
        if (curr->left) {
            Node* temp = curr->left;
            while (temp->right && temp->right != curr) temp = temp->right;
            if (!temp->right) {
                temp->right = curr;
                curr = curr->left;
            } else if (temp->right == curr) {
                temp->right = nullptr;
                count++;
                curr = curr->right;
            }
        } else {
            count++;
            curr = curr->right;
        }
    }
    return count;
}

float findMedianNodes (Node* root, int n) {
    int count = 0;
    int odd = (n+1)/2, oddVal = -1;
    int even1 = n/2, even1Val = -1;
    int even2 = (n/2)+1, even2Val = -1;
    Node* curr = root;
    while (curr) {
        if (curr->left) {
            Node* temp = curr->left;
            while (temp->right && temp->right != curr) temp = temp->right;
            if (!temp->right) {
                temp->right = curr;
                curr = curr->left;
            } else if (temp->right == curr) {
                temp->right = nullptr;
                int num = ++count;
                if (num == odd) oddVal = curr->data;
                if (num == even1) even1Val = curr->data;
                if (num == even2) even2Val = curr->data;
                curr = curr->right;
            }
        } else {
            int num = ++count;
            if (num == odd) oddVal = curr->data;
            if (num == even1) even1Val = curr->data;
            if (num == even2) even2Val = curr->data;
            curr = curr->right;
        }
    }
    if (n%2 == 0) { //even case
        return (even1Val+even2Val)/(float)2;
    } else {
        return oddVal;
    }
}

float findMedian(struct Node *root)
{
      //Code here
    int count = countOfNodes (root);
    return findMedianNodes (root, count);
}

// Check whether BST contains Dead End : 
bool checkDead (Node* root, unordered_map<int, bool>& map) {
    if (!root) return false;
    map[root->data] = true;
    if (!root->left && !root->right) {
        int xm = (root->data == 1) ? 1 : root->data-1;
        if (map.find(xm) != map.end() && map.find(root->data+1) != map.end()) return true;
        else return false;
    }
    bool checkLeft = checkDead(root->left, map);
    bool checkRight = checkDead(root->right, map);
    return checkLeft || checkRight;
}

bool isDeadEnd(Node *root)
{
    //Your code here
    unordered_map<int, bool> map;
    return checkDead (root, map);
}

// Range Sum of BST : 
int rangeSumBST(TreeNode* root, int low, int high) {
    if (!root) return 0;
    long long int sum = 0;
    if (root->val >= low && root->val <= high) sum += root->val;
    sum += rangeSumBST (root->left, low, high);
    sum += rangeSumBST (root->right, low, high);
    return sum;
}

// Flatten BST To a Linked List :
void generate(TreeNode<int> *root, TreeNode<int> *&node) {
  if (root) {
      generate (root->left, node);
      node->left = nullptr;
      node->right = root;
      node = root;
      generate (root->right, node);
  }
}

TreeNode<int>* flatten(TreeNode<int>* root) {
    // Write your code here
    if (!root) return nullptr;
    TreeNode<int>* node = new TreeNode<int>(-1);
    TreeNode<int>* curr = node;
    generate (root, curr);
    curr->left = curr->right = nullptr;
    return node->right;
}

// Replace every element with the least greater element on its right :
Node* insertElement (Node* root, int data, int& succ) {
    if (!root) return new Node(data);
    if (root->data > data) {
        succ = root->data;
        root->left = insertElement(root->left, data, succ);
    } else {
        root->right = insertElement(root->right, data, succ);
    }
    return root;
}
vector<int> findLeastGreater(vector<int>& arr, int n) {
    Node* root = nullptr;
    vector<int> arr1(n, -1);
    for (int i = arr.size()-1; i >= 0; i--) {
        int succ = -1;
        root = insertElement(root, arr[i], succ);
        arr1[i] = succ;
    }
    return arr1;
}

// Valid BST from Preorder
void buildBST (vector<int>& arr, int minI, int maxI, int& ind) {
    if (ind >= arr.size()) return;
    if (arr[ind] < maxI && arr[ind] > minI) {
        int ele = arr[ind++];
        buildBST (arr, minI, ele, ind);
        buildBST (arr, ele, maxI, ind);;
    }
}

int Solution::solve(vector<int> &A) {
    int minIndex = INT_MIN, maxIndex = INT_MAX, preIndex = 0;
    buildBST (A, minIndex, maxIndex, preIndex);
    return preIndex >= A.size();
}

// Merge two BST
void inorder (Node* root, vector<int>& arr) {
    if (root) {
        inorder(root->left, arr);
        arr.push_back(root->data);
        inorder(root->right, arr);
    }
}

vector<int> merge(Node *root1, Node *root2)
{
    //Your code here
    vector<int> arr1; vector<int> arr2;
    inorder(root1, arr1); inorder(root2, arr2);
  vector<int> resArr (arr1.size()+arr2.size(), -1);
  int k = 0, i = 0, j = 0;
  while (i < arr1.size() && j < arr2.size()) {
      if (arr1[i] < arr2[j]) {
          resArr[k++] = arr1[i++];
      } else {
          resArr[k++] = arr2[j++];
      }
  }
  while (i < arr1.size()) {
      resArr[k++] = arr1[i++];
  }
  while (j < arr2.size()) {
      resArr[k++] = arr2[j++];
  }
    return resArr;
}

// Binary Tree Maximum Path Sum (VVVV IMP!!!) : 
int recSol (TreeNode* root, int& maxI) {
    if (root == nullptr) {
        maxI = max (maxI, INT_MIN);
        return 0;
    }
    
    int ans = root->val;
    
    int left = recSol (root->left, maxI);
    int right = recSol (root->right, maxI);
    
    int sum = ans;
    if (left > 0) sum += left;
    if (right > 0) sum += right;
    maxI = max (maxI, sum);
    
    int sum1 = (max (left, right)) < 0 ? 0 : max (left, right);
    return (ans + sum1);
}

int maxPathSum(TreeNode* root) {
    int maxI = INT_MIN;
    recSol (root, maxI);
    return maxI;
}