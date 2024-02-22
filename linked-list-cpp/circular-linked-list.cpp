#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int data) {
        this->data = data;
        this->next = nullptr;
    }
};

class CircularLinkedList {
public:
    Node* head;
    int size;
    CircularLinkedList() {
        this->head = nullptr;
        size = 0;
    }
    void addHead (int val) {
        Node* newNode = new Node(val);
        if (this->head == nullptr) {
            this->head = newNode;
            newNode->next = this->head;
        } else {
            Node* p = this->head;
            while (p->next != this->head) {
                p = p->next;
            }
            p->next = newNode;
            newNode->next = this->head;
            this->head = newNode;
        }
        this->size++;
    }
    void addEnd (int val) {
        Node* newNode = new Node(val);
        if (this->head == nullptr) {
            this->head = newNode;
            newNode->next = this->head;
        } else {
            Node* p = this->head;
            while (p->next != this->head) {
                p = p->next;
            }
            p->next = newNode;
            newNode->next = this->head;
        }
        this->size++;
    }
    void insertAfter (int num, int val) {
        if (this->size == 0) {
            return;
        }
        Node* p = this->head; bool found = false;
        do {
            if (p->data == num) {
                found = true;
                break;
            }
            p = p->next;
        } while (p != this->head);
        if (found) {
            Node* newNode = new Node(val); 
            Node* q = p->next;
            p->next = newNode;
            newNode->next = q;
            this->size++;
        }
    }
    void deleteNum (int num) {
        if (this->size >= 1) {
            if (this->size == 1 && this->head->data == num) {
                this->head = nullptr;
            } else if (this->head->data == num) {
                Node* p = this->head;
                while (p->next != this->head) {
                    p = p->next;
                }
                p->next = this->head->next;
                this->head = this->head->next;
            } else if (this->size > 1) {
                Node* p = this->head; bool found = false;
                do {
                    if (p->next->data == num) {
                        found = true;
                        break;
                    }
                    p = p->next;
                } while (p != this->head);
                if (found) {
                    Node* q = p->next;
                    p->next = q->next;
                    delete q;
                }
            }
            this->size--;
        }
    }
    void traverse () {
        if (this->size == 0 && this->head == nullptr) {
            cout << "Empty";
            return;
        }
        Node* p = this->head;
        do {
            cout << p->data << " ";
            p = p->next;
        } while (p != this->head);
    }
};

int main()
{
    vector<int> arr {1, 2, 3, 4, 5, 6, 9, 11};
    CircularLinkedList* ll = new CircularLinkedList();
    
    for (auto i : arr) {
        ll->addEnd(i);
    }
    
    ll->traverse();
    cout << endl;
    ll->insertAfter(11, 67);
    ll->traverse();
    ll->deleteNum(1);
    cout << endl;
    ll->traverse();

    return 0;
}