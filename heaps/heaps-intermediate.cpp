// Kth smallest element : 

int kthSmallest(int arr[], int l, int r, int k) {
    priority_queue<int> pq;
    for (int i = l; i < k; i++) {
        pq.push(arr[i]);
    }
    for (int i = k; i <= r; i++) {
        if (pq.top() > arr[i]) {
            pq.pop(); pq.push(arr[i]);
        }
    }
    return pq.top();
}

// Kth largest element : 
int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < k; i++) {
        pq.push(nums[i]);
    }
    for (int i = k; i < nums.size(); i++) {
        if (pq.top() < nums[i]) {
            pq.pop(); pq.push(nums[i]);
        }
    }
    return pq.top();
}

// Merge 2 max heaps.
void heapify (vector<int>& arr, int size, int ind) {
    int index = ind;
    while (index > 0) {
        int parent = (index-1)/2;
        if (arr[parent] < arr[index]) {
            swap (arr[parent], arr[index]);
            index = parent;
        } else break;
    }
}
vector<int> mergeHeaps(vector<int> &a, vector<int> &b, int n, int m) {
    // your code here
    for (auto i : b) {
        a.push_back(i);
        heapify(a, a.size(), a.size()-1);
    }
    return a;
}

// Convert BST to Min Heap : 
void inorder (Node* root, vector<int>& arr) {
	if (!root) return;
	inorder (root->left, arr);
	arr.push_back(root->data);
	inorder (root->right, arr);
}

void convertToHeap(Node* root, vector<int>& arr, int& index) {
	if (!root) return;
	root->data = arr[index++];
	convertToHeap (root->left, arr, index);
	convertToHeap (root->right, arr, index);
}

Node* convertBST(Node* root)
{
	vector<int> arr;
	inorder(root, arr);
	int index = 0;
	convertToHeap(root, arr, index);
	return root;
}

// Check if Binary Tree is complete : 
int countNodes (TreeNode* root) {
    if (!root) return 0;
    int leftCount = countNodes (root->left);
    int rightCount = countNodes (root->right);
    return 1 + leftCount + rightCount;
}
bool isComplete (TreeNode* root, int count, int index) {
    if (!root) return true;
    if (index > count) return false;
    bool leftComplete = isComplete (root->left, count, 2*index);
    bool rightComplete = isComplete (root->right, count, 2*index + 1);
    return leftComplete && rightComplete;
}
bool isCompleteTree(TreeNode* root) {
    int count = countNodes (root);
    return isComplete (root, count, 1);
}

// Merge K sorted arrays : 
vector<int> mergeKArrays(vector<vector<int>> arr, int K)
{
    //code here
    priority_queue<pair<int, int>, vector<pair<int, int>>, compare> pq;
    for (int i = 0; i < arr.size(); i++) {
        pq.push({arr[i][0], i}); arr[i].erase(arr[i].begin());
    }
    vector<int> finalList;
    while (!pq.empty()) {
        pair<int, int> p1 = pq.top(); pq.pop();
        finalList.push_back(p1.first);
        if (arr[p1.second].size() != 0) {
            pq.push({arr[p1.second][0], p1.second});
            arr[p1.second].erase(arr[p1.second].begin());
        }
    }
    return finalList;
}

// Merge K sorted Linked Lists : 
ListNode* mergeKLists(vector<ListNode*>& lists) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, compare> pq;
    for (int i = 0; i < lists.size(); i++) {
        if (lists[i]) {
            pq.push({lists[i]->val, i});
            lists[i] = lists[i]->next;
        }
    }
    ListNode* dummy = new ListNode(-1);
    ListNode* p = dummy;
    while (!pq.empty()) {
        pair<int, int> outP = pq.top(); pq.pop();
        p->next = new ListNode(outP.first);
        p = p->next;
        if (lists[outP.second]) {
            int data = lists[outP.second]->val;
            pq.push({data, outP.second});
            lists[outP.second] = lists[outP.second]->next;
        }
    }
    return dummy->next;
}

// Smallest Range covering elements from K lists : 
class Node {
public:
    int data, row, col;
    Node(int val, int i, int j){
        data = val; row = i; col = j;
    }
};

class compare {
public:
    bool operator()(Node*& n1, Node*& n2) {
        return n1->data > n2->data;
    }
};

vector<int> smallestRange(vector<vector<int>>& nums) {
    int minI = INT_MAX, maxI = INT_MIN;
    priority_queue<Node*, vector<Node*>, compare> pq;
    for (int i = 0; i < nums.size(); i++) {
        maxI = max (nums[i][0], maxI);
        minI = min (nums[i][0], minI);
        Node* newNode = new Node (nums[i][0], i, 0);
        pq.push(newNode);
    }
    int ansMin = minI, ansMax = maxI;
    while (!pq.empty()) {
        Node* newNode = pq.top(); pq.pop();
        minI = newNode->data;
        int arrRow = newNode->row;
        int arrCol = newNode->col;
        if (maxI - minI < ansMax-ansMin) {
            ansMax = maxI; ansMin = minI;
        }
        if (arrCol+1 >= nums[arrRow].size()) {
            break;
        } else {
            maxI = max(maxI, nums[arrRow][arrCol+1]);
            Node* addNode = new Node (nums[arrRow][arrCol+1], arrRow, arrCol+1);
            pq.push(addNode);
        }
    }
    return {ansMin, ansMax};
}

// Remove stones to minimize total : 
int minStoneSum(vector<int>& piles, int k) {
    priority_queue<int> pq;
    for (auto i : piles) pq.push(i);
    while (k > 0) {
        int topEle = pq.top(); pq.pop();
        topEle = ceil (topEle/2.0);
        pq.push(topEle);
        k--;
    }
    int ans = 0;
    while (!pq.empty()) {
        ans += pq.top(); pq.pop();
    }
    return ans;
}

// Reorganize String : 
class compare {
    public :
    bool operator()(pair<char, int>& p1, pair<char, int>& p2) {
        return p1.second < p2.second;
    }
};

class Solution {
public:
    string reorganizeString(string s) {
        priority_queue<pair<char, int>, vector<pair<char, int>>, compare> pq;
        unordered_map<char, int> map;
        for (auto c: s) map[c]++;
        for (auto i: map) {
            pq.push({i.first, i.second});
        }
        string str = "";
        while (pq.size() > 1) {
            auto p1 = pq.top(); pq.pop();
            auto p2 = pq.top(); pq.pop();
            p1.second--; p2.second--;
            str += p1.first;
            str += p2.first;
            if (p1.second > 0) pq.push(p1);
            if (p2.second > 0) pq.push(p2);
        }
        if (pq.size() == 1) {
            if (pq.top().second > 1) return "";
            else str += pq.top().first;
        }
        return str;
    }
};

// Longest Happy String (Leetcode) : 
class compare {
    public :
    bool operator()(pair<char, int>& p1, pair<char, int>& p2) {
        return p1.second < p2.second;
    }
};

class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        priority_queue<pair<char, int>, vector<pair<char, int>>, compare> pq;
        if (a > 0) pq.push({'a', a});
        if (b > 0) pq.push({'b', b});
        if (c > 0) pq.push({'c', c});
        string str = "";
        while (pq.size() > 1) {
            auto p1 = pq.top(); pq.pop();
            auto p2 = pq.top(); pq.pop();

            if (p1.second >= 2) {
                str += string(2, p1.first);
                p1.second -= 2;
            } else {
                str += p1.first; p1.second--;
            }

            if (p2.second >= 2 && p2.second >= p1.second) {
                str += string(2, p2.first);
                p2.second -= 2;
            } else {
                str += p2.first; p2.second--;
            }

            if (p1.second > 0) pq.push(p1);
            if (p2.second > 0) pq.push(p2);
        }
        if (pq.size() == 1) {
            if (pq.top().second >= 2) str += string(2, pq.top().first);
            else str += pq.top().first;
        }
        return str;
    }
};

// K closest points to Origin : 
class Node {
public: 
    int x, y;
    double distance;
    Node (double dist, int xI, int yI) {
        distance = dist; x = xI; y = yI;
    }
};

class compare {
public:
    bool operator()(Node*& n1, Node*& n2) {
        return n1->distance > n2->distance;
    }
};

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        vector<vector<int>> ans;
        priority_queue<Node*, vector<Node*>, compare> pq;
        for (auto coor: points) {
            double dist = sqrt((coor[0]*coor[0])+(coor[1]*coor[1]));
            Node* n = new Node(dist, coor[0], coor[1]);
            pq.push(n);
        }
        while (k > 0) {
            Node* n = pq.top(); pq.pop();
            ans.push_back({n->x, n->y});
            k--;
        }
        return ans;
    }
};

// Get 3 biggest Rhombus Sums in Grid : 
vector<int> getBiggestThree(vector<vector<int>>& grid) {
    priority_queue<int> pq;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            pq.push(grid[i][j]);
            int aI = i, aJ = j;
            int bI = i+1, bJ = j-1;
            int cI = i+2, cJ = j;
            int dI = i+1, dJ = j+1;
            while (bJ >= 0 && bI < grid.size() && cI < grid.size() && dJ < grid[0].size() && dI < grid.size()) {
                int sum = grid[bI][bJ] + grid[aI][aJ] + grid[cI][cJ] + grid[dI][dJ];
                for (int x = aI+1, y = aJ-1; x < bI && y > bJ; x++, y--) {sum += grid[x][y];}
                for (int x = bI+1, y = bJ+1; x < cI && y < cJ; x++, y++) {sum += grid[x][y];}
                for (int x = cI-1, y = cJ+1; x > dI && y < dJ; x--, y++) {sum += grid[x][y];}
                for (int x = dI-1, y = dJ-1; x > aI && y > aJ; x--, y--) {sum += grid[x][y];}
                pq.push(sum);
                bI++; bJ--; cI += 2; dI++; dJ++;
            }
        }
    }
    int k = 3;
    vector<int> ans;
    while (!pq.empty() && ans.size() < 3) {
        int topEle = pq.top();
        pq.pop();
        if (ans.size() > 0 && ans.back() != topEle) ans.push_back(topEle);
        else if (ans.size() == 0) ans.push_back(topEle);
    }
    return ans;
}
