#include <bits/stdc++.h>
using namespace std;

// Initialize Trie
class TrieNode {
  public: 
  char data; TrieNode* children[26]; bool isTerminal;
  TrieNode (char c) {
    data = c;
    for (int i = 0; i < 26; i++) children[i] = nullptr;
    isTerminal = false;
  }
};

// Insert Word In Trie
void insertIntoTrie (TrieNode* root, string str) {
  if (str.size() == 0) {
    root->isTerminal = true;
    return;
  }

  TrieNode* childRef = root->children[str[0]-'a'];

  if (!childRef) {
    root->children[str[0]-'a'] = new TrieNode (str[0]);
    childRef = root->children[str[0]-'a'];
  } 

  insertIntoTrie (childRef, str.substr(1));
}

// Search Word In Trie
bool search (TrieNode* root, string str) {
  if (str.size() == 0) return root->isTerminal;

  TrieNode* childRef = root->children[str[0]-'a'];

  if (!childRef) {
    return false;
  }

  return search (childRef, str.substr(1));
}

// Delete Word From Trie
void deleteFromTrie (TrieNode* root, string str) {
  if (str.size() == 0) {
    root->isTerminal = false;
    return;
  }

  TrieNode* child = root->children[str[0]-'a'];

  if (!child) return;
  deleteFromTrie (child, str.substr(1));
}

int main() {
  TrieNode* root = new TrieNode ('-');
  insertIntoTrie (root, "dolph");
  insertIntoTrie (root, "dolphin");
  insertIntoTrie (root, "doll");
  insertIntoTrie (root, "code");
  insertIntoTrie (root, "coder");
  insertIntoTrie (root, "coding");
  insertIntoTrie (root, "whisk");
  insertIntoTrie (root, "whisky");
  insertIntoTrie (root, "whistle");
  cout << ((search(root, "cody")) ? "Present" : "Absent");
}

// Longest Common Starting Substring for an array of strings :
class TrieNode {
public : 
    char data; TrieNode* children[26]; bool isTerminal; int childCount, firstChildIndex;
    TrieNode (char val) {
        data = val;
        for (int i = 0; i < 26; i++) children[i] = nullptr;
        isTerminal = false;
        childCount = 0; firstChildIndex = -1;
    }
};

void insertIntoTrie (TrieNode* root, string word) {
    for (auto c: word) {
        if (!root->children[c-'a']) {
            root->childCount++; 
            if (root->childCount == 1) root->firstChildIndex = (c-'a');
            root->children[c-'a'] = new TrieNode (c);
        }
        root = root->children[c-'a'];
    }
    root->isTerminal = true;
}

string search (TrieNode* root) {
    string str = "";
    while (root->childCount == 1 && !root->isTerminal) {
        str += ('a' + root->firstChildIndex);
        root = root->children[root->firstChildIndex];
    }

    return str;
}

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        TrieNode* root = new TrieNode ('-');
        for (auto i : strs) {
            insertIntoTrie (root, i);
        }
        return search(root);
    }
};