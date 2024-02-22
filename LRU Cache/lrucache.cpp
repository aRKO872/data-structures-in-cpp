// Implement an LRU cache

class Node {
public:
    Node* next;
    Node* prev;
    int data, time;
    
    Node (int d, int t) {
        data = d; time = t;
        next = nullptr;
        prev = nullptr;
    }
};

class LRUCache {
public:
    unordered_map<int, Node*> mp;
    Node* head;
    Node* tail;
    int size;
    
    LRUCache(int capacity) {
        size = capacity;
        head = new Node (0, 0);
        tail = new Node (0, 0);
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if (mp.find(key) != mp.end() && mp[key] != nullptr) {
            Node* present = mp[key];
            Node* pastNode = present->prev;
            Node* futureNode = present->next;
            present->next = nullptr; present->prev = nullptr;
            pastNode->next = futureNode;
            futureNode->prev = pastNode;
            Node* newNext = head->next;
            head->next = present; present->prev = head;
            newNext->prev = present; present->next = newNext;
            mp[key] = head->next;
            return mp[key]->time;
        } else {
            return -1;
        }
    }
    
    void put(int key, int value) {
        if (mp.find(key) != mp.end() && mp[key] != nullptr) {
            Node* present = mp[key];
            present->time = value;
            Node* pastNode = present->prev;
            Node* futureNode = present->next;
            present->next = nullptr; present->prev = nullptr;
            pastNode->next = futureNode;
            futureNode->prev = pastNode;
            Node* newNext = head->next;
            head->next = present; present->prev = head;
            newNext->prev = present; present->next = newNext;
            mp[key] = head->next;
        } else {
            Node* newNode = new Node (key, value);
            if (size > 0) {
                
                size--;
                
            } else {
                
                Node* leastUsedNode = tail->prev;
                leastUsedNode->prev->next = tail;
                tail->prev = leastUsedNode->prev;
                leastUsedNode->next = nullptr; leastUsedNode->prev = nullptr;
                mp[leastUsedNode->data] = nullptr;
                
            }
            
            Node* newNext = head->next;
            newNode->prev = head; head->next = newNode;
            newNode->next = newNext; newNext->prev = newNode;
            
            mp[key] = head->next;
        }
    }
};