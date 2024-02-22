#include <bits/stdc++.h>
using namespace std;

class DNode {
public:
    int data;
    DNode* next;
    DNode* prev;
    DNode (int val) {
        this->data = val;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

class DoublyLinkedList {
public:
    DNode* head;
    int size;
    DoublyLinkedList () {
        this->head = nullptr;
        this->size = 0;
    }
    
    void addHead (int val) {
        DNode* newNode = new DNode(val);
        if (this->head == nullptr) {
            this->head = newNode;
        } else {
            DNode* p = this->head;
            newNode->next = p;
            p->prev = newNode;
            this->head = newNode;
        }
        this->size++;
    }
    
    void addTail (int val) {
        DNode* newNode = new DNode (val);
        if (this->head == nullptr) {
            this->head = newNode;
        } else {
            DNode* p = this->head;
            while (p->next != nullptr) {
                p = p->next;
            }
            p->next = newNode;
            newNode->prev = p;
        }
        this->size++;
    }
    
    void insertAtIndex (int index, int val) {
        if (this->head == nullptr) {
            if (index == 0) {
                this->addHead (val);
            }
            return;
        }
        if (index <= this->size) {
            if (index == 0) {
                this->addHead (val);
            } else if (index == this->size) {
                this->addTail (val);
            } else if (index < this->size) {
                DNode* newNode = new DNode (val);
                DNode* p = this->head; int count = 0;
                while (count < index-1) {
                    count++; p = p->next;
                }
                DNode* q = p->next;
                newNode->next = q;
                q->prev = newNode;
                p->next = newNode;
                newNode->prev = p;
                this->size++;
            }
        }
    }
    
    void deleteFirst () {
        if (this->head != nullptr) {
            DNode* q = this->head->next;
            this->head->next = nullptr;
            if (q != nullptr) {
                q->prev = nullptr;
            }
            this->head = q;
            this->size--;
        }
    }
    
    void deleteAtInd (int index) {
        if (index < this->size) {
            if (index == 0) {
                this->deleteFirst();
            } else {
                DNode* p = this->head; int count = 0;
                while (count < index-1) {
                    p = p->next; count++;
                }
                DNode* q = p->next;
                p->next = q->next;
                if (q->next != nullptr) {
                    q->next->prev = p;
                }
                q->next = nullptr; q->prev = nullptr;
                delete q; this->size--;
            }
        }
    }
    
    void traverse () {
        DNode* p = this->head;
        bool flag = false;
        while (p != nullptr) {
            flag = true;
            cout << p->data << " ";
            p = p->next;
        }
        if (flag == false) {
            cout << "Empty";
        }
        cout << endl;
    }
};

int main()
{
    vector<int> arr {1, 2, 3, 4, 5, 6, 9, 11};
    DoublyLinkedList* ll = new DoublyLinkedList();
    
    for (auto i : arr) {
        ll->insertAtIndex(ll->size, i);
    }
    
    ll->traverse();
    ll->insertAtIndex(1, 87);
    ll->traverse();
    ll->deleteAtInd(0);
    ll->traverse();

    return 0;
}