//Reverse K Elements in queue : 
queue<int> reverseK(queue<int> q, int k) {
    // add code here.
    int count = 0, total = q.size(); stack<int> st; queue<int> q1;
    while (count < total) {
        if (count+k > total) {
            int j = total-count;
            while (j > 0) {
                q1.push(q.front()); q.pop(); j--;
            }
            while (!q1.empty()) {
                q.push(q1.front()); q1.pop();
            }
            break;
        }
        int tmp = k;
        while (tmp > 0) {st.push(q.front()); q.pop(); tmp--;}
        while (!st.empty()) {q.push(st.top()); st.pop();}
        count += k;
    }
    return q;
}

//Reverse First K elements only : 
queue<int> modifyQueue(queue<int> q, int k) {
    stack<int> st; int count = 0, n = q.size();
    while (count < k) {
        int ele = q.front(); q.pop();
        st.push(ele);
        count++;
    }
    while (!st.empty()) {
        int ele = st.top(); q.push(ele); st.pop();
    }
    while (count < n) {
        int ele = q.front(); q.pop(); q.push(ele); count++;
    }
    return q;
}

//Reverse a Queue : 
void reverse (queue<int>& q) {
    if (q.empty()) return;
    int ele = q.front(); q.pop();
    reverse(q);
    q.push(ele);
}
queue<int> rev(queue<int> q)
{
    // add code here.
    reverse(q);
    return q;
}

//Interleave Queue : 
void interLeaveQueue(queue < int > & q) {
    int n = q.size()/2, count = 0; 
    queue<int> q1;
    while (count < n) {
        q1.push(q.front()); q.pop();
        count++;
    }
    while (!q1.empty()) {
        q.push(q1.front());
        q.push(q.front());
        q.pop(); q1.pop();
    }
}

//First Negative Integer in window of Size K : 
vector<long long> printFirstNegativeInteger(long long int A[],
                                             long long int N, long long int K) {
    vector<long long> res;
    queue<long long> q;
    for (long long i = 0; i < K; i++) {
        if (A[i] < 0) q.push(i);
    }
    if (q.empty()) res.push_back(0);
    else res.push_back(A[q.front()]);
    for (long long i = K; i< N; i++) {
        if (!q.empty() && i-K == q.front()) q.pop();
        if (A[i] < 0) q.push(i);
        if (q.empty()) res.push_back(0);
        else res.push_back(A[q.front()]);
    }
    return res;
 }

 //First Non Repeating Character in a Stream : 
 string FirstNonRepeating(string A){
    queue<char> q; string res = "";
    vector<int> alphaVec (26, 0);
    for (auto c : A) {
        q.push(c); alphaVec[c-'a']++;
        while (!q.empty() && alphaVec[q.front()-'a'] > 1) q.pop();
        if (q.empty()) res += '#';
        else res += q.front();
    }
    return res;
}

//Gas Station Problem (Leetcode : Super Super Important!!!) : 
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int balance = 0, deficit = 0, start = 0;
    for (int i = 0; i < gas.size(); i++) {
        balance += gas[i] - cost[i];
        if (balance < 0) {
            deficit += abs(balance);
            balance = 0;
            start = i + 1;
        }
    }
    if (deficit <= balance) {
        return start;
    }
    return -1;
}

//Maximum Sliding Window (Leetcode : Super Super Important!!!) :
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq; vector<int> ans;
    for (int i = 0; i < k; i++) {
        while (!dq.empty() && nums[i] >= nums[dq.back()]) dq.pop_back();
        dq.push_back(i);
    }
    ans.push_back(nums[dq.front()]);
    for (int i = k; i < nums.size(); i++) {
        if (i-k == dq.front()) dq.pop_front();
        while (!dq.empty() && nums[i] >= nums[dq.back()]) dq.pop_back();
        dq.push_back(i);
        ans.push_back(nums[dq.front()]);
    }
    return ans;
}