
// Climbing Stairs Leetcode problem
int process (int n, unordered_map<int, int>& map) {
    if (map.find(n) != map.end()) {
        return map[n];
    }
    map[n] = (process(n-1, map) + process(n-2, map));
    return map[n];
}

int climbStairs(int n) {
    unordered_map<int, int> map;
    map[0] = 0; map[1] = 1; map[2] = 2;
    return process(n, map);
}

//Print Maximum by recursion
int print(int arr[], int size, int i, int maxNum) {
    if (i == size) return maxNum;
    return print(arr, size, i+1, max(maxNum, arr[i]));
}

//print minimum by recursion
int printMin(int arr[], int size, int i, int minNum) {
    if (i == size) return minNum;
    return printMin(arr, size, i+1, min(minNum, arr[i]));
}

//find first occurence of character in string
int firstOccurence (string& name, int ind, char target) {
    if (ind == name.length()) return -1;
    return firstOccurence(name, ind+1, target);
    if (name[ind] == target) return ind;
}

//find last occurence of character in string
int lastOccurence (string& name, int ind, char target, int store) {
    if (ind == name.length()) {
        return store;
    }
    if (name[ind] == target) store = ind;
    return lastOccurence(name, ind+1, target, store);
}

//find all occurences of character in string
vector<int> occurences (string& name, int ind, char key, vector<int>& store) {
    if (ind == name.length()) return store;
    if (name[ind] == key) store.push_back(ind);
    return occurences(name, ind+1, key, store);
}

//check if array is sorted
bool isSorted (int arr[], int size, int ind) {
    if (ind >= size-1) return true;
    if (arr[ind] > arr[ind+1]) return false;
    return isSorted(arr, size, ind+1);
}

//binary search recursive
int findInd (vector<int>& arr, int st, int end, int target) {
  if (st > end) return -1;
  int mid = st + (end-st)/2;
  if (arr[mid] == target) return mid;
  else if (arr[mid] > target) return findInd(arr, st, mid-1, target);
  else return findInd(arr, mid+1, end, target);
}