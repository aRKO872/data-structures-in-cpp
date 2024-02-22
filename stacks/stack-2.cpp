int longestValidParentheses(string s) {
    int store = 0;
    stack<int> st; st.push(-1);
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') st.push(i);
        else {
            if (!st.empty()) {
                st.pop();
                
                if (!st.empty()) store = max(store, (i-st.top()));

                else st.push(i);
            }
        }
    }
    return store;
}

//Find next smaller element : 
vector<int> help_classmate(vector<int> arr, int n) 
{ 
    // Your code goes here
    vector<int> arr1;
    stack<int> st; st.push(-1);
    for (int i = n-1; i >= 0; i--) {
        while (st.top() >= arr[i]) {
            st.pop();
        }
        arr1.push_back(st.top());
        st.push(arr[i]);
    }
    reverse(arr1.begin(), arr1.end());
    return arr1;
} 

//Find previous smaller element : 
vector<int> leftSmaller(int n, int a[]){
    // code here
    vector<int> arr;
    stack<int> st; st.push(-1);
    for (int i = 0; i < n; i++) {
        while (st.top() >= a[i]) {
            st.pop();
        }
        arr.push_back(st.top());
        st.push(a[i]);
    }
    return arr;
}

//Largest Rectangle in Histogram (Very Very important): 
vector<int> generatePrev (vector<int>& heights) {
    vector<int> arr;
    stack<int> st; st.push(-1);
    for (int i = 0; i < heights.size(); i++) {
        while (st.top() != -1 && heights[st.top()] >= heights[i]) {
            st.pop();
        }
        arr.push_back(st.top());
        st.push(i);
    }
    return arr;
}
vector<int> generateNext (vector<int>& heights) {
    vector<int> arr;
    stack<int> st; st.push(-1);
    for (int i = heights.size()-1; i >= 0; i--) {
        while (st.top() != -1 && heights[st.top()] >= heights[i]) {
            st.pop();
        }
        arr.push_back(st.top());
        st.push(i);
    }
    reverse(arr.begin(), arr.end());
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == -1) arr[i] = heights.size();
    }
    return arr;
}
int largestRectangleArea(vector<int>& heights) {
    vector<int> nextArr = generateNext (heights);
    vector<int> prevArr = generatePrev (heights);
    int maxSum = 0, currSum = 0;
    for (int i = 0; i < heights.size(); i++) {
        int width = nextArr[i]-prevArr[i]-1;
        maxSum = max (maxSum, (width*heights[i]));
    }
    return maxSum;
}

//Count the number of brackets which can be reversed to make a proper bracket (Important):
int countRev (string s)
{
    // your code here
    if (s.size() == 0) return 0;
    if (s.size()%2 != 0) return -1;
    stack<char> st;
    for (auto c: s) {
        if (!st.empty() && st.top() == '{' && c == '}') {st.pop(); continue;}
        st.push(c);
    }
    if (st.empty()) return 0;
    string s1 = "";
    while (!st.empty()) {
        s1 += st.top(); st.pop();
    }
    reverse(s1.begin(), s1.end());
    int count = 0;
    for (int i = 1; i < s1.size(); i += 2) {
        if (s1[i] == s1[i-1]) count++;
        else if (s1[i] == '{' && s1[i-1] == '}') count += 2;
    }
    return count;
} 

//Give index for element, which is known by everyone, but doesn't know anyone. (The celebrity problem-Important) :
int celebrity(vector<vector<int> >& M, int n) 
{
    // code here 
    stack<int> st;
    for (int i = 0; i < n; i++) st.push(i);
    int a, b;
    while (st.size() > 1) {
        a = st.top(); st.pop();
        b = st.top(); st.pop();
        if (M[a][b]) st.push(b);
        else st.push(a);
    }
    int res = st.top();
    for (int i = 0; i < n; i++) if (M[res][i]) return -1;
    for (int i = 0; i < n; i++) if (!M[i][res] && i != res) return -1;
    return res;
}

//Next Greater Node in Linked List : 
void nextLargerRec (ListNode* head, stack<int>& st, vector<int>& arr) {
    if (head == nullptr) return;
    nextLargerRec (head->next, st, arr);
    while (!st.empty() && st.top() <= head->val) st.pop();
    int arrData = (st.empty()) ? 0 : st.top();
    arr.push_back(arrData);
    st.push(head->val);
}
vector<int> nextLargerNodes(ListNode* head) {
    stack<int> st;
    vector<int> arr;
    nextLargerRec(head, st, arr);
    reverse(arr.begin(), arr.end());
    return arr;
}

//Online Stock Span (Leetcode):
class StockSpanner {
public:
    stack<pair<int, int>> st;
    StockSpanner() {
    }
    
    int next(int price) {
        int span = 1;
        while (!st.empty() && st.top().first <= price) {
            span += st.top().second; st.pop();
        }
        st.push({price, span});
        return span;
    }
};

//Check if Word is valid after substitutions (Leetcode-Important) :
bool isValid(string s) {
    stack<char> st;
    for (auto c: s) {
        if (st.empty() || st.size() == 1) st.push(c);
        else {
            char first = st.top(); st.pop(); 
            char second = st.top();
            if (first == 'b' && second == 'a' && c == 'c') st.pop();
            else {
                st.push(first); st.push(c);
            }
        }
    }
    return st.empty();
} 

//Decode String - Leetcode (VV Important) : 
string decodeString(string s) {
    stack<string> st;
    string S = "";
    for (auto c: s) {
        if (c == ']') {
            string minS = "";
            while (!st.empty() && st.top() != "[") {minS += st.top(); st.pop();}
            st.pop();
            string numS = "";
            while (!st.empty() && isdigit(st.top()[0])) {numS += st.top(); st.pop();}
            reverse(numS.begin(), numS.end());
            int num = stoi(numS);
            string resS = "";
            while (num > 0) {resS += minS; num--;}
            st.push(resS);
        } else {
            st.push(string(1, c));
        }
    }
    while (!st.empty()) {S += st.top(); st.pop();}
    reverse(S.begin(), S.end());
    return S;
}

//Car FLeet-I Problem (Important-Leetcode) : 
int carFleet(int target, vector<int>& position, vector<int>& speed) {
    vector<pair<int, int>> posSpeed;
    for (int i = 0; i < position.size(); i++) {
        posSpeed.push_back({position[i], speed[i]});
    }
    sort(posSpeed.begin(), posSpeed.end(), [](pair<int, int> p1, pair<int, int> p2){
        return p1.first < p2.first;
    });
    stack<float> st;
    for (auto p: posSpeed) {
        float time = (target - p.first)/((float)p.second);
        while (!st.empty() && st.top() <= time) {
            st.pop();
        }
        st.push(time);
    }
    return st.size();
}

//Car Fleet-II Problem (Important-Leetcode) :
vector<double> getCollisionTimes(vector<vector<int>>& cars) {
    stack<int> st;
    vector<double> res (cars.size(), -1);
    for (int i = cars.size()-1; i >= 0; i--) {
        double p = cars[i][0], s = cars[i][1];
        while (!st.empty()) {
            double p2 = cars[st.top()][0], s2 = cars[st.top()][1];
            if (s <= s2 || ((p2-p)/(s - s2) > res[st.top()] && res[st.top()] > 0)) {
                st.pop();
            } else {
                break;
            }
        }
        if (!st.empty()) {
            res[i] = (cars[st.top()][0]-p) / (s-cars[st.top()][1]);
        }
        st.push(i);
    }
    return res;
}

//Simplify Path (Important-Leetcode) : 
string simplifyPath(string path) {
    stack<string> st; int i = 0;
    while (i < path.size()) {
        string minS = ""; minS += path[i]; i++;
        while (i < path.size() && path[i] != '/') { minS += path[i]; i++;}
        if (minS == "/" || minS == "/.") continue;
        if (minS == "/..") {
            if (!st.empty()) st.pop(); 
            continue;
        }
        st.push(minS);
    }
    string res = "";
    while (!st.empty()) {
        res = st.top() + res;
        st.pop();
    }
    return res == "" ? "/" : res;
}

//Maximal Rectangle (Important-Leetcode) : 
vector<int> generateNext (vector<int>& store) {
    stack<int> st; st.push(-1);
    vector<int> res;
    for (int i = store.size()-1; i >= 0; i--) {
        while (!st.empty() && st.top() != -1 && store[st.top()] >= store[i]) {
            st.pop();
        }
        res.push_back(st.top());
        st.push(i);
    }
    reverse(res.begin(), res.end());
    for (int i = 0; i < res.size(); i++) if (res[i] == -1) res[i] = res.size();
    return res;
}
vector<int> generatePrev (vector<int>& store) {
    stack<int> st; st.push(-1);
    vector<int> res;
    for (int i = 0; i < store.size(); i++) {
        while (!st.empty() && st.top() != -1 && store[st.top()] >= store[i]) {
            st.pop();
        }
        res.push_back(st.top());
        st.push(i);
    }
    return res;
}
int maximalRectangle(vector<vector<char>>& matrix) {
    vector<int> store(matrix[0].size(), 0);
    int maximum = 0;
    for (auto arr: matrix) {
        for (int i = 0; i < arr.size(); i++) store[i] = (arr[i] == '0') ? 0 : (store[i] + 1);
        vector<int> nextArr = generateNext (store);
        vector<int> prevArr = generatePrev (store);
        int currMax = 0;
        for (int i = 0; i < store.size(); i++) {
            int width = nextArr[i]-prevArr[i]-1;
            currMax = max(currMax, width*store[i]);
        }
        maximum = max(currMax, maximum);
    }
    return maximum;
}