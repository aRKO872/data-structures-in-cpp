// Convert Sorted Array into Binary Search Tree
Node* bstRec (vector<int>& nums, int st, int end) {
    if (st > end) return nullptr;
    int mid = st + (end-st)/2;
    Node* root = new Node(nums[mid]);
    root->right = bstRec (nums, mid+1, end);
    root->left = bstRec (nums, st, mid-1);
    return root;
}
Node* sortedArrayToBST(vector<int>& nums) {
    Node* root = bstRec (nums, 0, nums.size()-1);
    return root;
}

// Insert into Binary Search Tree From Array, along with Searching and Deleting In BST : 
class Node {
  public : 
  int data;
  Node* left; 
  Node* right;
  Node (int data) {
    this->data = data;
    left = nullptr;
    right = nullptr;
  } 
};

class BST {
  public:
  Node* insertElement (Node* root, int element) {
    Node* newNode = new Node (element);
    if (!root) return newNode;
    if (root->data < element) {
      root->right = insertElement(root->right, element);
    } else {
      root->left = insertElement(root->left, element);
    }
    return root;
  }

  Node* searchBST(Node* root, int val) {
      if (root == nullptr) return nullptr;
      if (root->data == val) return root;
      if (root->data < val) {
          return searchBST (root->right, val);
      } else {
          return searchBST (root->left, val);
      }
  }

  int minimum (Node* root) {
    if (!root->left) return root->data;
    return minimum (root->left);
  }
  // Find Minimum in BST
  int minValue(Node* root) {
      if (root == nullptr) return -1;
      return minimum (root);
  }

  int maximum (Node* root) {
    if (!root->right) return root->data;
    return maximum (root->right);
  }
  // Find Maximum in BST
  int maxValue(Node* root) {
      if (root == nullptr) return -1;
      return maximum (root);
  }

  //Deletion In BST: 
  int predecessor (Node* root) {
      if (!root->right) return root->data;
      return predecessor (root->right);
  }
  Node* deleteNode(Node* root, int key) {
      if (!root) return root;
      if (root->data < key) root->right = deleteNode (root->right, key);
      else if (root->data > key) root->left = deleteNode (root->left, key);
      else {
          if (!root->left && !root->right) return nullptr;
          if (!root->left) return root->right;
          else if (!root->right) return root->left;
          root->data = predecessor (root->left);
          root->left = deleteNode (root->left, root->data);
      }
      return root;
  }

  void inorderTraversal (Node* root) {
    if (root != nullptr) {
      inorderTraversal (root->left);
      cout << root->data << " ";
      inorderTraversal (root->right);
    }
  }
};

int main() {
  vector<int> arr = {1, 7, 8, 3, 4, 2, -1, -3, -4, 10};
  BST* bst = new BST(); Node* root = nullptr;
  for (auto i: arr) {
    root = bst->insertElement(root, i);
  }
  bst->inorderTraversal(root);
}

// Search in a BST : 
TreeNode* searchBST(TreeNode* root, int val) {
    if (root == nullptr) return nullptr;
    if (root->val == val) return root;
    if (root->val < val) {
        return searchBST (root->right, val);
    } else {
        return searchBST (root->left, val);
    }
}

// Validate if binary tree is a BST : 
bool isValidRec (TreeNode* root, long long int highLimit, long long int lowLimit) {
    if (!root) return true;
    bool leftVal = isValidRec (root->left, root->val, lowLimit);
    bool rightVal = isValidRec (root->right, highLimit, root->val);
    bool currVal = (root->val > lowLimit && root->val < highLimit);
    return leftVal && rightVal && currVal;
}
bool isValidBST(TreeNode* root) {
    long long int high = 214748364800;
    long long int low = -214748364800;
    return isValidRec (root, high, low);
}

// Lowest Common Ancestor in a Binary Search Tree
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root) return nullptr;
    if (root == p || root == q) return root; 
    if (root->val > p->val && root->val > q->val) return lowestCommonAncestor (root->left, p, q);
    if (root->val < p->val && root->val < q->val) return lowestCommonAncestor (root->right, p, q);
    return root;
}

// Kth Smallest Element in a BST
void kthSmallestRec (TreeNode* root, int k, int& count, int& ans) {
    if (!root) return;
    kthSmallestRec (root->left, k, count, ans);
    count++;
    if (count == k) {
        ans = root->val;
        return;
    }
    kthSmallestRec (root->right, k, count, ans);
}
int kthSmallest(TreeNode* root, int k) {
    int count = 0; int ans = 0;
    kthSmallestRec (root, k, count, ans);
    return ans;
}

// Search if 2 elements in BST can form target value : 
void inorder (TreeNode* root, vector<int>& arr) {
    if (root) {
        inorder (root->left, arr);
        arr.push_back(root->val);
        inorder (root->right, arr);
    }
}
bool findTarget(TreeNode* root, int k) {
    if (!root->left && !root->right) return false;
    vector<int> arr; inorder (root, arr);
    int lo = 0, hi = arr.size()-1;
    while (lo < hi) {
        if (arr[lo] + arr[hi] == k) return true;
        if (arr[lo]+arr[hi] > k) hi--;
        else lo++; 
    }
    return false;
}

// Balance a Binary Search Tree
void inorder (TreeNode* root, vector<int>& arr) {
    if (root) {
        inorder(root->left, arr); arr.push_back(root->val); inorder (root->right, arr);
    }
}
TreeNode* arrToBST (vector<int> arr, int st, int end) {
    int mid = st + (end-st)/2;
    TreeNode* root = new TreeNode(arr[mid]);
    if (st == end) return root;
    if (st > end) return nullptr;
    root->left = arrToBST (arr, st, mid-1);
    root->right = arrToBST (arr, mid+1, end);
    return root;
}
TreeNode* balanceBST(TreeNode* root) {
    vector<int> inorderArr;
    inorder(root, inorderArr);
    int st = 0, end = inorderArr.size()-1;
    TreeNode* ans = arrToBST (inorderArr, st, end);
    return ans;
}

// In place BST to sorted DLL : 
void generate(TreeNode<int> *root, TreeNode<int> *&head) {
    if (!root) return;
    generate (root->right, head);
    root->right = head;
    if (head) head->left = root;
    head = root;
    generate (root->left, head);
}

TreeNode<int>* bstToSortedDLL(TreeNode<int> *root)
{
    TreeNode<int>* head = nullptr;
    generate (root, head);
    return head;
}

// Convert Sorted List to Binary Search Tree : 
ListNode* getMid (ListNode* head) {
    ListNode* fast = head; ListNode* slow = head; ListNode* prevSlow = slow;
    while (fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next; prevSlow = slow; slow = slow->next;
    } 
    prevSlow->next = nullptr;
    return slow;
}
TreeNode* sortedListToBST(ListNode* head) {
    if (!head) return nullptr;
    if (!head->next) return new TreeNode(head->val);
    ListNode* mid = getMid (head);
    TreeNode* root = new TreeNode(mid->val);
    root->left = sortedListToBST (head);
    root->right = sortedListToBST (mid->next);
    return root;
}

// Inorder successor in a BST : 
Node * inOrderSuccessor(Node *root, Node *x) {
    Node* successor = nullptr;
    Node* curr = root;
    while (curr) {
        if (curr->data > x->data) {
            successor = curr;
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return successor;
}