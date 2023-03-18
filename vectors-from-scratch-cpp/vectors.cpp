#include <iostream>
#include <vector>
using namespace std;

int findUnique(vector<int> arr) {           //This approach is very important as it uses XoR operation
  int xorSum = 0;
  for (int i = 0; i < arr.size(); i++) {
    xorSum = xorSum ^ arr[i];
  }
  return xorSum;
}

vector<int> intersection (vector<int> a, vector<int> b, int sizeA, int sizeB) {
  vector<int> inter;
  int i = 0, j = 0;
  if (sizeB < sizeA) {
    while (i < sizeA) {
      if (a[i] == b[j]) {
        inter.push_back(a[i]);
        j++;
      }
      i++;
    }
  } else {
    while (j < sizeB) {
      if (b[j] == a[i]) {
        inter.push_back(b[j]);
        i++;
      }
      j++;
    }
  }
  
  return inter;
}

vector<int> sortedUnion(vector<int> a, vector<int> b, int sizeA, int sizeB) {
  vector<int> sorted;
  int i = 0, j = 0;
  while(i < sizeA && j < sizeB) {
    if (a[i] > b[j]) {
      sorted.push_back(b[j++]);
    } else {
      sorted.push_back(a[i++]);
    }
  }
  while (i < sizeA) {
    sorted.push_back(a[i++]);
  }
  while (j < sizeB) {
    sorted.push_back(b[j++]);
  }
  return sorted;
}

int main () {
  int list1[] = {1, 2, 3, 3, 4, 6, 8};
  int list2[] = {3, 3, 4, 9, 10};
  int size1 = sizeof(list1)/sizeof(int);
  int size2 = sizeof(list2)/sizeof(int);
  vector<int> arr1(list1, list1+size1);
  vector<int> arr2(list2, list2+size2);
  vector<int> res = intersection(arr1, arr2, size1, size2);
  cout << "The intersection is ";
  for (int i = 0; i < res.size(); i++) {
    cout << res[i] << " ";
  }
}