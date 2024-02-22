class Heap {
  vector<int> heapArr;
  int size;

  Heap() {
    size = 0;
    heapArr[size] = -1;
  }
  
  void insertIntoHeap (int data) {
    size++;
    heapArr.push_back(data);
    int index = size;
    while (index > 1) {
      int parent = index/2;
      if (heapArr[parent] < heapArr[index]) {
        int temp = heapArr[parent];
        heapArr[parent] = heapArr[index];
        heapArr[index] = temp;
        index = parent;
      } else {
        break;
      }
    }
  }

  int delete () {
    if (size == 0) return -1;
    size--;
    int returnedElement = heapArr[1];
    heapArr[1] = heapArr.back();
    heapArr.pop_back();
    int index = 1;
    while (index < size) {
      int left = 2* index;
      int right = 2*index + 1;
      int largest = index;
      if (left < heapArr.size() && heapArr[largest] < heapArr[left]) {
        largest = left;
      }
      if (right < heapArr.size() && heapArr[largest] < heapArr[right]) {
        largest = right;
      }
      if (largest != index) {
        int temp = heapArr[largest];
        heapArr[largest] = heapArr[index];
        heapArr[index] = temp;
        index = largest;
      } else {
        break;
      }
    }
    return returnedElement;
  }
}

// Heapify An Array (VVVVVV IMP!!!) : 
void heapify (vector<int> arr, int size, int ind) {
  int index = ind;
  int left = 2*index;
  int right = 2*index + 1;
  int largest = index;
  if (left < size && arr[largest] < arr[left]) {
    largest = left;
  }
  if (right < size && arr[largest] < arr[right]) {
    largest = right;
  }
  if (largest != index) {
    int temp = arr[largest];
    arr[largest] = arr[index];
    arr[index] = temp;
    heapify (arr, size, largest);
  } else {
    return;
  }
}

// Also very important!
void buildHeap (vector<int> arr) {
  for (int i = arr.size()/2; i > 0; i--) {
    heapify (arr, arr.size(), i);
  }
}

// Heap Sort (VVVVV Imp!) : 
void heapSort(vector<int>& arr) {
  buildHeap (arr);
  for (int i = arr.size()-1; i > 1; i--) {
    swap(arr[1], arr[i]);
    heapify (arr, i, 1);
  }
}

// Find Kth Smallest Element, using Max Heap : 
int kthSmallest(int arr[], int l, int r, int k) {
    priority_queue<int> pq;   // Max Heap
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

//Find Kth Largest element using Min Heap :
int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> pq;    // Min Heap
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

//Merge 2 Max-heaps :
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

//Validating if Binary Tree is a Heap : 
int countNodes (Node* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    int leftCount = countNodes(root->left);
    int rightCount = countNodes(root->right);
    return 1 + leftCount + rightCount;
}
bool isComplete (Node* root, int n, int index) {
    if (!root) return true;
    if (index > n) return false;
    bool leftComplete = isComplete(root->left, n, 2*index);
    bool rightComplete = isComplete(root->right, n, 2*index + 1);
    return leftComplete && rightComplete;
}
bool isHeapRec (Node* tree) {
    if (!tree) return true;
    bool isLeftHeap = isHeap (tree->left);
    bool isRightHeap = isHeap (tree->right);
    bool isCurrHeap = true;
    if (tree->left && tree->left->data > tree->data) isCurrHeap = false;
    if (tree->right && tree->right->data > tree->data) isCurrHeap = false;
    return isLeftHeap && isRightHeap && isCurrHeap;
}
bool isHeap(struct Node* tree) {
    // code here
    int count = countNodes(tree);
    if (!isComplete(tree, count, 1)) return false;
    return isHeapRec (tree);
}