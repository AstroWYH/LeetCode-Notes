```cpp
对于unit8_t来说，0x5转换成二进制后，第一个1的位置是5，且总共有2个1；
对于uint32_t来说，0x5转换成二进制后，第一个1的位置是29，也总共有2个1。
现在请你用C++写一个通用的算法，可以实现快速找到0x5的第一个1的位置，
以及一共有多少个1，不能用现成的函数，必须手写。
    
// 00000101
int count_ones(int n) {
  int count = 0;
  while (n) {
    // count += n & 1;
    if (n & 1 == 1) {
        count++;
    }
    n >>= 1;
  }
  return count; // 得到答案2
}

int find_first_one(int n) {
  int count = 0;
  while (n) {
    count++;
    n >>= 1;
  }
  return count; // 得到答案3
}
// 再获取位宽8 - 3 = 5;这一步还需要处理，未完待续。
```

