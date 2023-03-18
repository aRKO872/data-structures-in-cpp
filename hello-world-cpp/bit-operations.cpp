#include <iostream>
#include <cmath>
using namespace std;

int countBits (int num) {
  int count = 0;
  while (num > 0) {
    if (num&1) {
      count++;
    }
    num = num >> 1;
  }
  return count;
}

int decimalToBinary (int num) {
  int binaryNum = 0, i = 0;
  while (num > 0) {
    binaryNum = (num%2)*pow(10, i++) + binaryNum;
    num = num >> 1;
  }
  return binaryNum;
}

int binaryToDecimal (int bin) {
  int dec = 0, i = 0;
  while (bin > 0) {
    dec += (bin%10)*pow(2, i++);
    bin /= 10;
  }
  return dec;
}

int setKthBit(int N, int K){
    int shadow = 1 << K;        //create shadow to do OR with given N value.
    return (N | shadow);
}

int main () {
  int a;
  cin >> a;
  cout << "Binary is " << binaryToDecimal(a) << endl;
}