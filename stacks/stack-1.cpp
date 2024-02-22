class MyStack {
public:
    vector<int> arr;
    int size;
    MyStack() {
        this->size = 0;
    }
    
    void push(int x) {
        this->arr.push_back(x);
        this->size++;
    }
    
    int pop() {
        if (this->empty()) return -1;
        int poppedElement = this->arr[this->size-1];
        this->arr.pop_back();
        this->size--;
        return poppedElement;
    }
    
    int top() {
        if (this->empty()) return -1;
        return this->arr[this->size-1];
    }
    
    bool empty() {
        return this->size == 0;
    }
};

// Create two stacks using an array : 
class TwoInOne {
  public: 
  int arr*; int size, top1, top2;
  TwoInOne (int _size) {
    size = _size; top1 = -1; top2 = _size;
  }
  void push1(int x)
  {
      if (top2 - top1 == 1) return;
      top1++;
      arr[top1] = x; 
  }
  void push2(int x)
  {
      if (top2 - top1 == 1) return;
      top2--;
      arr[top2] = x; 
  }
  int pop1()
  {
      if (top1 == -1) return -1;
      int popped = arr[top1--];
      return popped;
  }
  int pop2()
  {
      if (top2 == size) return -1;
      int popped = arr[top2++];
      return popped;
  }
}

//Create N Stacks in an array : 
class NStack
{
public:
    // Initialize your data structure.
    int *top, *arr, *next;
    int freespot;
    NStack(int N, int S)
    {
        // Write your code here.
        arr = new int[S]; next = new int[S];
        top = new int[N];
        for (int i = 0; i < S-1; i++) {
            next[i] = i+1;
        }
        for (int i = 0; i < N; i++) {
            top[i] = -1;
        }
        next[S-1] = -1;
        freespot = 0;
    }

    // Pushes 'X' into the Mth stack. Returns true if it gets pushed into the stack, and false otherwise.
    bool push(int x, int m)
    {
        // Write your code here.
        int index = freespot;
        if (freespot == -1) return false;
        freespot = next[index];
        arr[index] = x;
        next[index] = top[m-1];
        top[m-1] = index;
        return true;
    }

    // Pops top element from Mth Stack. Returns -1 if the stack is empty, otherwise returns the popped element.
    int pop(int m)
    {
        // Write your code here.
        int index = top[m-1];
        if (top[m-1] == -1) return -1;
        top[m-1] = next[index];
        int store = arr[index];
        next[index] = freespot;
        freespot = index;
        return store;
    }
};

//Delete middle element of a stack (Important!):
void deleteRec (stack<int>&s, int totalSize, int delSize) {
    if (delSize == 0) return;
    int ele = s.top(); s.pop();
    deleteRec(s, totalSize, delSize-1);
    if (delSize != ((totalSize+1)/2)) s.push(ele);
}
void deleteMid(stack<int>&s, int sizeOfStack)
{
    deleteRec (s, sizeOfStack, sizeOfStack);
}

// Insert element at bottom of a stack : 
stack<int> pushAtBottom(stack<int>& myStack, int x) 
{
    // Write your code here.
    if (myStack.empty()) {
        myStack.push(x); return myStack;
    }
    int element = myStack.top();
    myStack.pop();
    pushAtBottom(myStack, x);
    myStack.push(element);
    return myStack;
}

//Reverse a stack : 
void insertBottom (stack<int>& s, int target) {
    if (s.empty()) {
        s.push(target); return;
    }
    int ele = s.top();
    s.pop();
    insertBottom (s, target);
    s.push(ele);
}
void Reverse(stack<int> &St){
    if (St.empty()) return;
    int ele = St.top();
    St.pop();
    Reverse (St);
    insertBottom (St, ele);
}

// Valid arrangement of Parentheses: 
bool isValid(string s) {
    stack<char> st;
    for (auto c: s) {
        if (st.empty() && (c == ')' || c == '}' || c == ']')) return false;
        else if (!st.empty() && ((st.top() == '(' && c == ')') || (st.top() == '{' && c == '}') || (st.top() == '[' && c == ']'))){
            st.pop();
        } else {
            st.push(c);
        }
    }
    return st.empty();
}

//Sort a stack : 
void insertInSortedStack (stack<int>& st, int x) {
    if (st.empty()) {
        st.push(x); return;
    }
    int ele = st.top();
    if (ele < x) {
        st.push(x); return;
    }
    st.pop();
    insertInSortedStack (st, x);
    st.push(ele);
}
void sortRec (stack<int>& st) {
    if (st.empty()) return;
    int ele = st.top();
    st.pop();
    sortRec(st);
    insertInSortedStack(st, ele);
}
void SortedStack :: sort()
{
   //Your code here
   sortRec(s);
}

//Check if any redundant brackets exist:
bool findRedundantBrackets(string &s)
{
    // Write your code here
    stack<char> st;
    for (auto c : s) {
        if (c == '(' || c == '+' || c == '-' || c == '/' || c == '*') {
            st.push(c);
        } else if (c == ')') {
            bool opFlag = false;
            while (!st.empty() && st.top() != '(') {
                char ele = st.top();
                if (ele == '+' || ele == '-' || ele == '/' || ele == '*') {
                    opFlag = true;
                }
                st.pop();
            }
            if (!opFlag) return true;
            st.pop();
        }
    }
    return false;
}

//Min-Stack : Get minimum element in stack at O(1) time.
public:
    int peek, minI;
    vector<pair<int, int>> arr;
    MinStack() {
        this->minI = -1;
        this->peek = -1; 
    }
    
    void push(int val) {
        if (this->peek == -1) {this->arr.push_back({val, val}); this->minI = val;}
        else {
            this->minI = min (this->minI, val);
            this->arr.push_back({val, this->minI});
        }
        this->peek++;
    }
    
    void pop() {
        if (this->peek == -1) return;
        this->peek--;
        this->arr.pop_back();
        this->minI = (arr.size() == 0) ? -1 : arr.back().second;
    }
    
    int top() {
        if (this->peek == -1) return -1;
        return this->arr[this->peek].first;
    }
    
    int getMin() {
        if (this->peek == -1) return -1;
        return this->arr[this->peek].second;
    }
};
