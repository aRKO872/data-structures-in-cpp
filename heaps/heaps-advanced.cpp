// Find Median from Data Stream (VVVVV Important!) : 
class MedianFinder {
public:
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
    double median;
    MedianFinder() {
        median = INT_MIN;
    }
    
    void addNum(int num) {
        int sizeMax = maxHeap.size(), sizeMin = minHeap.size();
        if (sizeMax == sizeMin) {
            if (num > median) {
                minHeap.push(num);
                median = minHeap.top();
            } else {
                maxHeap.push(num);
                median = maxHeap.top();
            }
        } else if (sizeMax < sizeMin) {
            if (num > median) {
                int topEle = minHeap.top(); minHeap.pop();
                maxHeap.push(topEle);
                minHeap.push(num);
            }  else {
                maxHeap.push(num);
            }
            median = (maxHeap.top() + minHeap.top())/2.0;
        } else {
            if (num > median) {
                minHeap.push(num);
            }  else {
                int topEle = maxHeap.top(); maxHeap.pop();
                minHeap.push(topEle);
                maxHeap.push(num);
            }
            median = (maxHeap.top() + minHeap.top())/2.0;
        }
    }
    
    double findMedian() {
        return median;
    }
};

// Sliding Window Max (VVV Important) : 
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> res; 
    priority_queue<pair<int, int>, vector<pair<int, int>>, compare> pq;
    for (int i = 0; i < k; i++) {
        pq.push({nums[i], i});
    }
    res.push_back(pq.top().first);
    for (int i = k; i < nums.size(); i++) {
        while (!pq.empty() && pq.top().second <= i-k){
            pq.pop();
        }
        pq.push({nums[i], i});
        res.push_back(pq.top().first);
    }
    return res;
}

// Minimum Difference in Sums after removal of Elements : 
long long minimumDifference(vector<int>& nums) {
    if (nums.size() == 1) return nums[0];
    priority_queue<long long int> maxHeap;
    priority_queue<long long int, vector<long long int>, greater<long long int>> minHeap;
    vector<long long int> minArr(nums.size(), -1);
    vector<long long int> maxArr(nums.size(), -1);
    int n = nums.size()/3, i = 0;
    long long int minSum = 0, maxSum = 0;
    while (i < nums.size()) {
        maxHeap.push(nums[i]);
        minSum += nums[i];
        if (maxHeap.size() > n) {
            minSum -= maxHeap.top();
            maxHeap.pop();
        }
        if (maxHeap.size() == n) {
            minArr[i] = minSum;
        }
        i++;
    }
    i--;
    while (i >= 0) {
        minHeap.push(nums[i]);
        maxSum += nums[i];
        if (minHeap.size() > n) {
            maxSum -= minHeap.top();
            minHeap.pop();
        }
        if (minHeap.size() == n) {
            maxArr[i] = maxSum;
        }
        i--;
    }
    i = n;
    long long int minDiff = LONG_LONG_MAX;
    while (i < (2*n)+1) {
        minDiff = min(minDiff, minArr[i-1]-maxArr[i]);
        i++;
    }
    return minDiff;
}

// Minimum number of Refueling Stops (VVVV Important!) : 
int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
    int stops = 0, stopCount = 0;
    priority_queue<int> pq;
    while (startFuel < target) {
        while (stopCount < stations.size()) {
            if (startFuel >= stations[stopCount][0]) pq.push(stations[stopCount][1]);
            else break;
            stopCount++;
        }
        
        if (pq.empty()) return -1;

        int dist = pq.top();
        pq.pop();

        startFuel += dist;
        
        stops++;
    }
    return stops;
}