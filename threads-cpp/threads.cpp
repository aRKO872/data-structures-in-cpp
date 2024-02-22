// My First Thread Code :
#include <bits/stdc++.h>
using namespace std;

void fun1 () {
    for (int i = 1; i <= 10; i++) {
        sleep(1);
        cout << "iTask " << i << endl; 
    }
}

void fun2 () {
    for (int i = 1; i <= 10; i++) {
        sleep(1);
        cout << "jTask " << i << endl;
    }
}

int main() {
    // Write C++ code here
    thread t1 (fun1);
    thread t2 (fun2);
    
    t1.join();
    t2.join();
    
    return 0;
}

// Mutual Exclusion to avoid Race Condition :
#include <bits/stdc++.h>
using namespace std;
mutex mtx;

void fun1 (int& count) {
    
    for (int i = 1; i <= 100000; i++) {
        mtx.lock();
        count++;
        mtx.unlock();
    }
}

int main() {
    // Write C++ code here
    int count = 0;
    thread t1 (fun1, std::ref(count));
    thread t2 (fun1, std::ref(count));
    
    t1.join();
    t2.join();
    
    cout << count;
    
    return 0;
}