class Node {
public:
    int data;
    Node* next;
    Node(int data) {
        this->data = data;
        this->next = nullptr;
    }
};

class LinkedList {
public:
    Node* head;
    int size;
    LinkedList() {
        this->head = nullptr;
        size = 0;
    }
    void addHead (int val) {
        Node* newNode = new Node(val);
        if (this->head == nullptr) {
            this->head = newNode;
        } else {
            newNode->next = this->head;
            this->head = newNode;
        }
        this->size++;
    }
    void addEnd (int val) {
        Node* newNode = new Node(val);
        if (this->head == nullptr) {
            this->head = newNode;
        } else {
            Node* p = this->head;
            while (p->next != nullptr) {
                p = p->next;
            }
            p->next = newNode;
        }
        this->size++;
    }
    void addAtIndex (int index, int val) {
        if (this->head == nullptr && index != 0) {
            return;
        }
        if (index == 0) {
            this->addHead(val);
        }else if (index == this->size) {
            this->addEnd(val);
        } else if (index < this->size) {
            Node* p = this->head; int i = 0;
            Node* newNode = new Node(val);
            while (i < index-1) {
                p = p->next; i++;
            }
            newNode->next = p->next;
            p->next = newNode;
            this->size++;
        }
    }
    void deleteAtIndex (int index) {
        if (this->head == nullptr) {
            return;
        }
        if (index == 0) {
            Node* p = this->head->next;
            delete this->head;
            this->head = p; this->size--;
        } else if (index < this->size) {
            Node* p = this->head; int i = 0;
            while (i < index-1) {
                p = p->next; i++;
            }
            p->next = p->next->next; this->size--;
        }
    }
    int get (int index) {
        if (index >= this->size) {
            return -1;
        } else {
            Node* p = this->head; int i = 0;
            while (i < index) {
                p = p->next; i++;
            }
            return p->data;
        }
    }
    void traverse () {
        Node* p = this->head;
        while (p != nullptr) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << "- " << this->size << endl;
    }
};

//Reverse a singly linked list recursively:
Node* reverseRec (Node*& prev, Node*& curr) {
    if (curr == nullptr) return prev;
    Node* forward = curr->next;
    curr->next = prev;
    return reverseRec (curr, forward);
}
Node* reverseList(Node* head) {
    Node* curr = head; Node* prev = nullptr;
    Node* p = reverseRec (prev, curr);
    return p;
}

//Reverse a singly linked list iteratively:
Node* reverseList(Node* head) {
    Node* prev = nullptr; Node* curr = head;
    while (curr != nullptr) {
        Node* forward = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forward;
    }
    return prev;
}

//Find middle of a linked list :
Node* middleNode(Node* head) {
    Node* slow = head; Node* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

//Reverse linked list in groups of k (vvvv Important):
int length (Node* head) {
    if (head == nullptr) return 0;
    return 1+length(head->next);
}
Node* reverseKGroup(Node* head, int k) {
    if (head == nullptr) return head;
    int len = length(head);
    if (k > len) return head;
    Node* prev = nullptr; Node* curr = head;
    Node* temp = head; int count = 0;
    while (count != k && curr != nullptr) {
        Node* forward = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forward;
        count++;
    }
    head->next = reverseKGroup (curr, k);
    return prev;
}

//Check if linked list is circular or not : 
bool isSol (Node* p, Node* head) {
    if (p == nullptr) return false;
    if (p == head) return true;
    return isSol (p->next, head);
}

bool isCircular(Node *head)
{
   // Your code here
   if (head == nullptr) return true;
   return isSol (head->next, head);
}

// Check if linked list has cycle in it or not (VVVV Important):
bool hasCycle(Node *head) {
    Node* fast = head; Node* slow = head;
    while (fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow) return true;
    }
    return false;
}

//Find starting point of cycle if there is a cycle in the linked list (VVVVV Important):
Node *detectCycle(Node *head) {
    Node* fast = head; Node* slow = head;
    while (fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow) {
            slow = head;
            while (slow != fast) {
                slow = slow->next; 
                fast = fast->next;
            }
            return fast;
        }
    }
    return nullptr;
}

//Find and remove loop in linked list (VVVV Important) :
void removeLoop(Node* head)
{
    // code here
    // just remove the loop without losing any nodes
    Node* fast = head; Node* slow = head;
    while (fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;
        if (slow == fast) {
            slow = head; 
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            Node* q = slow;
            while (q->next != slow) {
                q = q->next;
            }
            q->next = nullptr;
            break;
        }
    }
}

//Check if LL is palindrome or not? :
bool isPalindrome(Node* head) {
    if (head->next == nullptr) return true;
    Node* slow = head; Node* fast = head;
    while (fast->next != nullptr && fast->next->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;
    }
    Node* curr = slow->next; Node* prev = nullptr;
    while (curr != nullptr) {
        Node* forward = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forward;
    }
    slow->next = prev;
    Node* head1 = head; Node* head2 = prev;
    while (head2 != nullptr) {
        if (head1->data != head2->data) return false; 
        head1 = head1->next; head2 = head2->next;
    }
    return true;
}

//Remove Duplicates from sorted LL :
Node* deleteDuplicates(Node* head) {
    Node* p = head;
    while (p != nullptr && p->next != nullptr) {
        if (p->next->data == p->data) {
            Node* q = p->next;
            p->next = q->next;
            q->next = nullptr;
            delete q;
        } else {
            p = p->next;
        }
    }
    return head;
}

//Function to sort a linked list of 0s, 1s and 2s.
Node* segregate(Node *head) {
    // Add code here
    Node* l1 = new Node(-1); Node* l0 = new Node(-1); Node* l2 = new Node(-1); 
    Node* s1 = l1; Node* s2 = l2; Node* s0 = l0;
    Node* p = head;
    while (p != nullptr) {
        Node* forward = p->next; 
        if (p->data == 0) {
            l0->next = p; l0 = l0->next;
        } else if (p->data == 1) {
            l1->next = p; l1 = l1->next;
        } else {
            l2->next = p; l2 = l2->next;
        }
        p->next = nullptr;
        p = forward;
    }
    Node* q = new Node(-1); Node* q1 = q;
    if (s0->next != nullptr) {
        q->next = s0->next; 
        q = l0;
    }
    if (s1->next != nullptr) {
        q->next = s1->next; 
        q = l1;
    }
    if (s2->next != nullptr) {
        q->next = s2->next; 
        q = l2;
    }
    return q1->next;
}

//Add two numbers represented as linked lists :
Node* reverse(Node* prev, Node* curr) {
    if (curr == nullptr) return prev;
    Node* forward = curr->next;
    curr->next = prev;
    return reverse(curr, forward);
}
Node* addHead (Node* l, int val) {
    Node* newNode = new Node(val);
    if (l == nullptr) {
        l = newNode;
    } else {
        newNode->next = l;
        l = newNode;
    }
    return l;
}
Node* addTwoNumbers(Node* l1, Node* l2) {
    Node* ans = nullptr; Node* p1 = l1; Node* p2 = l2; int carry = 0;
    while (p1 != nullptr && p2 != nullptr) {
        int sum = p1->data + p2->data + carry;
        ans = addHead(ans, sum%10);
        carry = sum/10;
        p1 = p1->next; p2 = p2->next;
    }
    while (p1 != nullptr) {
        int sum = p1->data + carry;
        ans = addHead(ans, sum%10);
        carry = sum/10;
        p1 = p1->next;
    }
    while (p2 != nullptr) {
        int sum = p2->data + carry;
        ans = addHead(ans, sum%10);
        carry = sum/10;
        p2 = p2->next;
    }
    while (carry > 0) {
        ans = addHead(ans, carry%10);
        carry /= 10;
    }
    ans = reverse(nullptr, ans);
    return ans;
}

//merge 2 sorted linked list:
Node* mergeTwoLists(Node* list1, Node* list2) {
    Node* dummy = new Node (0); Node* dummyIt = dummy;
    while (list1 != nullptr && list2 != nullptr) {
        if (list1->data < list2->data) {
            dummyIt->next = list1; dummyIt = dummyIt->next;
            Node* temp = list1->next; 
            list1->next = nullptr;
            list1 = temp;
        } else {
            dummyIt->next = list2; dummyIt = dummyIt->next;
            Node* temp = list2->next; 
            list2->next = nullptr;
            list2 = temp;
        }
    }
    if (list1 != nullptr) {
        dummyIt->next = list1;
    }
    if (list2 != nullptr) {
        dummyIt->next = list2;
    }
    return dummy->next;
}

// Merge Nodes in between zeroes :
Node* mergeNodes(Node* head) {
    Node* dummy = new Node(-1); Node* p = dummy;
    Node* q = head->next; int currSum = 0; int count = 1;
    while (q != nullptr) {
        if (q->data == 0) {
            p->data = currSum;
            p->next = nullptr;
            currSum = 0;
            count = 1;
        } else {
            if (count == 1) {
                p->next = q; p = p->next;
            }
            currSum += q->data;
            count++;
        }
        q = q->next;
    }
    return dummy->next;
}

// Delete N Nodes after skipping M Nodes : 
void linkdelete(struct Node  *head, int M, int N) {
    //Add code here
    if (M == 0 && N == 0) return;
    if (M == 0) return;
    if (N == 0) return;
    Node* dummy = new Node(-1); dummy->next = head; Node* p = dummy;
    while (p != nullptr) {
        int countM = 0, countN = 0;
        while (p != nullptr && countM < M) {
            p = p->next; countM++;
        }
        if (p == nullptr || p->next == nullptr) break;
        while (p->next != nullptr && countN < N) {
            p->next = p->next->next; countN++;
        }
    }
    head = dummy->next;
}

//Find Minimum and Maximum Number of Nodes between critical points (Leetcode) : 
vector<int> nodesBetweenCriticalPoints(Node* head) {
    vector<int> arr;
    int pos = 2, back = head->data;
    Node* p = head->next;
    while (p->next != nullptr) {
        if ((back > p->data && p->next->data > p->data) || (back < p->data && p->next->data < p->data)) {
            arr.push_back(pos);
        }
        back = p->data;
        p = p->next; pos++;
    }
    if (arr.size() <= 1) return {-1, -1}; 
    int maxI = arr.back() - arr[0];
    int minI = INT_MAX;
    for (int i = 1; i < arr.size(); i++) {
        minI = min(arr[i]-arr[i-1], minI);
    }
    return {minI, maxI};
}

//Rotate Linked List K times to the right:
int length (Node* head) {
    if (head == nullptr) return 0;
    return 1 + length(head->next);
}
Node* rotateRight(Node* head, int k) {
    int len = length(head);
    if (len <= 1 || k == 0) return head;
    int count = 1; Node* p = head;
    while (count < (len-(k%len))) {
        count++;
        p = p->next;
    }
    if (p->next == nullptr) return head;
    Node* q = p->next;
    p->next = nullptr;
    Node* r = q;
    while (r->next != nullptr) {
        r = r->next;
    }
    r->next = head;
    head = q;
    return head;
}

//Split Linked List in Parts (Leetcode) :
int length(Node* head) {
    if (head == nullptr) return 0;
    return 1+length(head->next);
}
void sol (vector<Node*>& ans, Node* head, int ind) {
    if (head == nullptr) return;
    Node* p = head->next;
    head->next = nullptr;
    ans[ind] = head;
    sol (ans, p, ind+1);
}
vector<Node*> splitListToParts(Node* head, int k) {
    int len = length(head);
    int sizeOfPart = len/k;
    int buffer = len%k, index = 0;
    vector<Node*> ans (k);
    if (len <= k) {
        sol(ans, head, index);
        return ans;
    }
    Node* p = head;
    while (p != nullptr) {
        int count = 1;
        Node* q = p;
        while (count < sizeOfPart) {
            count++; q = q->next;
        }
        if (buffer > 0) {
            buffer--; q = q->next;
        }
        if (q == nullptr) {
            ans[index++] = p;
            break;
        }
        Node* r = q->next;
        q->next = nullptr;
        ans[index++] = p;
        p = r;
    }
    return ans;
} 

// Arrange all odd indexed element together and even elements together, maintaining order:
Node* oddEvenList(Node* head) {
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr) return head;
    Node* odd = head; Node* even = head->next; Node* even1 = head->next;
    while (even != nullptr && even->next != nullptr) {
        odd->next = odd->next->next; odd = odd->next;
        even->next = even->next->next; even = even->next;
    }
    odd->next = even1;
    return head;
}

//Reverse linked list from index left to index right:
Node* reverseBetween(Node* head, int left, int right) {
    if (left == right) return head;
    Node* dummy = new Node(-1); dummy->next = head;
    Node* p = dummy; int countL = 0; Node* q = p;
    while (countL < left) {
        q = p; p = p->next; countL++;
    }
    Node* curr = p; Node* prev = nullptr; int countK = 0;
    while (curr != nullptr && countK < right-left+1) {
        Node* forward = curr->next; countK++;
        curr->next = prev;
        prev = curr;
        curr = forward;
    }
    if (curr != nullptr) p->next = curr;
    q->next = prev;
    return dummy->next;
}

// Delete N number node from the back : 
void removeNthNode (Node* head, int n, int& p) {
    if (head == nullptr) {
        return;
    }
    removeNthNode (head->next, n, p);
    p++;
    if (n+1 == p) {
        head->next = head->next->next;
    }
}
Node* removeNthFromEnd(Node* head, int n) {
    int p = 0;
    Node* dummy = new Node(-1, head);
    removeNthNode(dummy, n, p);
    return dummy->next;
}

//Delete Middle node of linked list :
Node* deleteMiddle(Node* head) {
    if (head->next == nullptr) return nullptr;
    Node* slow = head; Node* slowBack = head; Node* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slowBack = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    slowBack->next = slow->next;
    slow->next = nullptr;
    delete slow;
    return head;
}

//Reorder List (Leetcode) : 
void reorderList(Node* head) {
    if (head->next == nullptr || head->next->next == nullptr) return;
    Node* slow = head; Node* fast = head;
    while (fast->next != nullptr && fast->next->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;
    }
    Node* curr = slow->next; Node* prev = nullptr;
    while (curr != nullptr) {
        Node* forward = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forward;
    }
    slow->next = nullptr;
    Node* head1 = head; Node* head2 = prev;
    while (head1 != nullptr && head2 != nullptr) {
        Node* tmp1 = head1->next; Node* tmp2 = head2->next;
        head1->next = head2; head2->next = tmp1;
        head1 = tmp1; head2 = tmp2;
    }
}

// Merge Sort Linked List:
int length (Node* head) {
    if (head == nullptr) return 0;
    return 1+length(head->next);
}
Node* merge (Node* list1, Node* list2) {
    Node* dummy = new Node(-1); Node* dummyIt = dummy;
    while (list1 != nullptr && list2 != nullptr) {
        if (list1->data < list2->data) {
            dummyIt->next = list1; dummyIt = dummyIt->next;
            Node* temp = list1->next; 
            list1->next = nullptr;
            list1 = temp;
        } else {
            dummyIt->next = list2; dummyIt = dummyIt->next;
            Node* temp = list2->next; 
            list2->next = nullptr;
            list2 = temp;
        }
    }
    if (list1 != nullptr) {
        dummyIt->next = list1;
    }
    if (list2 != nullptr) {
        dummyIt->next = list2;
    }
    return dummy->next;
}
Node* mergeSort (Node* head, int len) {
    if (len < 2) {
        return head;
    }
    int firstLen = len/2;
    int secondLen = len-firstLen;
    int count = 1; Node* p = head;
    while (count < firstLen) {
        count++; p = p->next;
    }
    Node* head1 = p->next;
    p->next = nullptr;
    Node* updated1 = mergeSort (head, firstLen);
    Node* updated2 = mergeSort (head1, secondLen);
    head = merge (updated1, updated2);
    return head;
}
Node* sortList(Node* head) {
    int len = length(head);
    return mergeSort (head, len);
}

//Flattening a linked list : 
Node* merge (Node* head1, Node* head2) {
    Node* ans = new Node(-1); Node* ansIt = ans;
    while (head1 != nullptr && head2 != nullptr) {
        if (head1->data > head2->data) {
            ansIt->bottom = head2; ansIt = ansIt->bottom;
            Node* temp = head2->bottom;
            head2->bottom = nullptr;
            head2 = temp;
        } else {
            ansIt->bottom = head1; ansIt = ansIt->bottom;
            Node* temp = head1->bottom;
            head1->bottom = nullptr;
            head1 = temp;
        }
    }
    if (head1 != nullptr) {
        ansIt->bottom = head1;
    }
    if (head2 != nullptr) {
        ansIt->bottom = head2;
    }
    return ans->bottom;
}
Node *flatten(Node *root)
{
   // Your code here
   Node* p = root;
   Node* ans = nullptr;
   while (p != nullptr) {
       ans = merge(ans, p);
       p = p->next;
   }
   return ans;
}

//Merge k Sorted Linked Lists : 
Node* merge(Node* list1, Node* list2) {
        Node* dummy = new Node(-1); Node* p = dummy;
        Node* h1 = list1; Node* h2 = list2;
        while (h1 != nullptr && h2 != nullptr) {
            if (h1->data > h2->data) {
                p->next = h2; Node* forward = h2->next;
                h2->next = nullptr; h2 = forward;
            } else {
                p->next = h1; Node* forward = h1->next; 
                h1->next = nullptr; h1 = forward;
            }
            p = p->next;
        }
        if (h1 != nullptr) {
            p->next = h1;
        }
        if (h2 != nullptr) {
            p->next = h2;
        }
        return dummy->next;
    }
    Node* mergeKLists(vector<Node*>& lists) {
        Node* dummy = new Node(-1); Node* p = dummy;
        for (auto list: lists) {
            p->next = merge(p->next, list);
            p = dummy;
        }
        return p->next;
    }

//Flatten Multilevel Linked List (Leetcode) :
Node* flatten(Node* head) {
    Node* p = head;
    while (p != nullptr) {
        if (p->child == nullptr) {
            p = p->next; continue;
        }
        Node* temp = p->child;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = p->next;
        if (p->next != nullptr) p->next->prev = temp;
        Node* childTemp = p->child;
        p->next = childTemp;
        p->child = nullptr;
        childTemp->prev = p;
        p = childTemp;
    }
    return head;
}

// copy linked list from random pointer : 
Node* copyRandomList(Node* head) {
    if (head == nullptr) return head;
    Node* p = head;
    while (p != nullptr) {
        Node* newNode = new Node(p->val);
        Node* store = p->next;
        p->next = newNode;
        newNode->next = store;
        p = store;
    }
    Node* first = head;;
    while (first != nullptr) {
        Node* second = first->next;
        if (first->random != nullptr) {
            second->random = first->random->next;
        } 
        first = first->next->next;
    }
    first = head; Node* second = head->next; Node* second1 = second;
    while (second->next != nullptr) {
        first->next = first->next->next;
        second->next = second->next->next;
        first = first->next; second = second->next;
    }
    first->next = nullptr;
    return second1;
}