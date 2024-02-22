// Two Unique Pairs existing having same Sum : 
int findPairs(long long a[], long long n) {
    unordered_map<long long int, int> map2;
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (map2[a[i]+a[j]] > 0) return 1;
            map2[a[i]+a[j]]++;
        }
    }
    return 0;
}

// Largest SubArray with 0 sum : 
int maxLen(vector<int>&A, int n)
{
    int res = 0;
    unordered_map<int, int> map;
    int currSum = 0;
    map[0] = -1;
    for (int i = 0; i < n; i++) {
        currSum += A[i];
        if (map.find(currSum) != map.end()) {
            int dist = i-map[currSum];
            res = max (res, dist);
        } else {
            map[currSum] = i;
        }
    }
    return res;
}

// largest subarray of 0s and 1s : 
int maxLen(int arr[], int N)
{
    unordered_map<int, int> map;
    map[0] = -1;
    int currSum = 0, largest = 0;
    for (int i = 0; i < N; i++) if (arr[i] == 0) arr[i] = -1;
    for (int i = 0; i < N; i++) {
        currSum += arr[i];
        if (map.find(currSum) == map.end()) {
            map[currSum] = i;
        } else {
            int dist = i - map[currSum];
            largest = max(dist, largest);
        }
    }
    return largest;
}

// Top K Frequent Words : 
class compare {
    public: 
    bool operator()(pair<string, int>& p1, pair<string, int>& p2) {
        if (p1.second == p2.second) return p1.first > p2.first;
        return p1.second < p2.second;
    }
};

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> map;
        priority_queue<pair<string,int>, vector<pair<string, int>>, compare> pq;
        for (auto s: words) map[s]++;
        for (auto m: map) pq.push({m.first, m.second});
        vector<string> res;
        while (k > 0) {
            auto topEle = pq.top(); pq.pop();
            res.push_back(topEle.first);
            k--;
        }
        return res;
    }
};

// Sort Array 1 on basis of Array 2 : 
vector<int> sortA1ByA2(vector<int> A1, int N, vector<int> A2, int M) 
{
    //Your code here
    map<int, int> mp;
    for (int i = 0; i < N; i++) {
        mp[A1[i]]++;
    }
    
    vector<int> ans;
    
    for (int i = 0; i < M; i++) {
        int freq = 0;
        if (mp.find(A2[i]) != mp.end() && mp[A2[i]] > 0) {
            freq = mp[A2[i]];
            mp[A2[i]] = 0;
        }
        
        for (int j = 0; j < freq; j++) {
            ans.push_back(A2[i]);
        }
    }
    
    for (auto m: mp) {
        int freq = m.second;
        while (freq > 0) {
            ans.push_back(m.first);
            freq--;
        }
    }
    
    return ans;
} 

// Counting Elements in 2 arrays (VVVVV IMP!!) : 
int findLongestInd (vector<int>& arr, int x) {
    int st = 0, end = arr.size()-1, res = 0;
    while (st <= end) {
        int mid = st + (end-st)/2;
        if (arr[mid] <= x) {
            res = mid+1;
            st = mid+1;
        } else {
            end = mid-1;
        }
    }
    
    return res;
}
vector<int> countEleLessThanOrEqual(int arr1[], int arr2[], int m, int n)
{
//Your code goes here
    vector<int> ar1; vector<int> ar2;
    for (int i = 0; i < m; i++) ar1.push_back(arr1[i]);
    for (int i = 0; i < n; i++) ar2.push_back(arr2[i]);
    
    sort (ar2.begin(), ar2.end());
    vector<int> ans;
    unordered_map<int, int> mp;
    for (int i = 0; i < m; i++) {
        if (mp.find(ar1[i]) != mp.end()) {
            ans.push_back(mp[ar1[i]]);
        } else {
            mp[ar1[i]] = findLongestInd (ar2, ar1[i]);
            ans.push_back(mp[ar1[i]]);
        }
    }
    return ans;
}

// Check Subarray Sum Divisible by K, with length at least 2 : 
bool checkSubarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> mp;
    mp[0] = -1;
    int total = 0;
    
    for (int i = 0; i < nums.size(); i++) {
        total += nums[i];
        if (mp.find(total%k) == mp.end()) {
            mp[total%k] = i;
        } else if (mp[total%k] <= i-2) {
            return true;
        }
    }
    
    return false;
}