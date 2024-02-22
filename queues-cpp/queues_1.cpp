//Classic Queue Implementation : 
class MyQueue {
private:
    int arr[100005];
    int front;
    int rear;

public :
    MyQueue(){front=0;rear=0;}
    void push(int);
    void push(int x){
          arr[rear++] = x; 
    }
    int pop()
    {    
          if (front == rear) return -1;
          return arr[front++];
    }
};

// Circular Queue Implementation (VVVV Important) : 
class MyCircularQueue {
public:
    int* arr; int front, rear, size;
    MyCircularQueue(int k) {
        front = rear = -1; 
        size = k;
        arr = new int[k];
    }
    
    bool enQueue(int value) {
        if (rear == -1) {
            front++; rear++; arr[rear] = value;
        } else if (isFull()) {
            return false;
        } else if (rear == size-1 && front != 0) {
            rear = 0; arr[rear] = value;
        } else {
            arr[++rear] = value;
        }
        return true;
    }
    
    bool deQueue() {
        if (isEmpty()) {
            return false;
        } else if (rear == front) {
            rear = -1; front = -1;
        } else if (front == size-1) {
            front = 0;
        } else {
            front++;
        }
        return true;
    }
    
    int Front() {
        if (isEmpty()) return -1;
        return arr[front];
    }
    
    int Rear() {
        if (isEmpty()) return -1;
        return arr[rear];
    }
    
    bool isEmpty() {
        return (rear == -1 && front == -1);
    }
    
    bool isFull() {
        return ((rear == size-1 && front == 0) || (rear == front-1));
    }
};

//Implement Circular Deque : 
class MyCircularDeque {
public:
    int* arr; int front, rear, size;
    MyCircularDeque(int k) {
        front = rear = -1;
        arr = new int[k];
        size = k;
    }
    
    bool insertFront(int value) {
        if (isEmpty()) {
            front++; rear++;
        } else if (isFull()) {
            return false;
        } else if (front == 0 && rear != size-1) {
            front = size-1;
        } else {
            front--;
        }
        arr[front] = value;
        return true;
    }
    
    bool insertLast(int value) {
        if (isEmpty()) {
            front++; rear++;
        } else if (isFull()) {
            return false;
        } else if (rear == size-1 && front != 0) {
            rear = 0;
        } else {
            rear++;
        }
        arr[rear] = value; return true;
    }
    
    bool deleteFront() {
        if (isEmpty()) {
            return false;
        } else if (rear == front) {
            arr[front] = -1; front = -1; rear = -1;
        } else if (front == size-1) {
            arr[front] = -1; front = 0;
        } else {
            arr[front] = -1; front++;
        }
        return true;
    }
    
    bool deleteLast() {
        if (isEmpty()) return false;
        else if (rear == front) {
            arr[rear] = -1; rear = -1; front = -1;
        } else if (rear == 0) {
            arr[rear] = -1; rear = size-1;
        } else {
            arr[rear] = -1; rear--;
        }
        return true;
    }
    
    int getFront() {
        if (isEmpty()) return -1;
        return arr[front];
    }
    
    int getRear() {
        if (isEmpty()) return -1;
        return arr[rear];
    }
    
    bool isEmpty() {
        return (rear == -1);
    }
    
    bool isFull() {
        return ((rear == size-1 && front == 0) || (rear == front-1));
    }
};

//Implement Stacks Using Queues : 
class MyStack {
public:
    queue<int> mainQ;
    queue<int> storeQ;
    MyStack() {
    }
    
    void push(int x) {
        while (!mainQ.empty()) {storeQ.push(mainQ.front()); mainQ.pop();}
        mainQ.push(x);
        while (!storeQ.empty()) {mainQ.push(storeQ.front()); storeQ.pop();}
    }
    
    int pop() {
        if (mainQ.empty()) return -1;
        int ele = mainQ.front();
        mainQ.pop();
        return ele;
    }
    
    int top() {
        if (mainQ.empty()) return -1;
        return mainQ.front();
    }
    
    bool empty() {
        return mainQ.empty();
    }
};

//Implement Queues using Stacks : 
class MyQueue {
public:
    stack<int> mainStack;
    stack<int> storeStack;
    MyQueue() {
        
    }
    
    void push(int x) {
        while (!mainStack.empty()) {storeStack.push(mainStack.top()); mainStack.pop();}
        mainStack.push(x);
        while (!storeStack.empty()) {mainStack.push(storeStack.top()); storeStack.pop();}
    }
    
    int pop() {
        if (mainStack.empty()) return -1;
        int ele = mainStack.top();
        mainStack.pop();
        return ele;
    }
    
    int peek() {
        if (mainStack.empty()) return -1;
        return mainStack.top();
    }
    
    bool empty() {
        return mainStack.empty();
    }
};

//Implement N Queues in an Array : 
class NQueue{
public:
    int* frontArr; int* rearArr; int* nextArr; int* arr; int freeSpot;
    NQueue(int n, int s){
        freeSpot = 0; 
        frontArr = new int[n];
        rearArr = new int[n];
        arr = new int[s];
        nextArr = new int[s];
        for (int i = 0; i < n; i++) {
            frontArr[i] = rearArr[i] = -1;
        }
        for (int i = 0; i < s - 1; i++) {
            nextArr[i] = i+1;
        }
        nextArr[s-1] = -1;
    }

    // Enqueues 'X' into the Mth queue. Returns true if it gets pushed into the queue, and false otherwise.
    bool enqueue(int x, int m){
        if (freeSpot == -1) return false;
        int index = freeSpot;
        freeSpot = nextArr[index];
        if (frontArr[m-1] == -1) {
            frontArr[m-1] = index;
        }else {nextArr[rearArr[m-1]] = index; }
        nextArr[index] = -1;
        rearArr[m-1] = index;
        arr[index] = x;
        return true;
    }

    // Dequeues top element from Mth queue. Returns -1 if the queue is empty, otherwise returns the popped element.
    int dequeue(int m){
        if (frontArr[m-1] == -1) return -1;
        int index = frontArr[m-1];
        frontArr[m-1] = nextArr[index];
        nextArr[index] = freeSpot;
        freeSpot = index;
        return arr[index];
    }
};