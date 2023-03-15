```cpp
分析：
首先，定义一个 bubbleSort 函数，接受两个参数，一个整数数组和数组的大小。
在函数内部，定义了两个循环变量 i 和 j，分别用于迭代数组中的元素。
通过变量 swapped 来记录是否发生了交换。在第一层循环中，我们假设数组已经排序完成，如果在当前循环中没有进行任何交换，则说明数组已经排序完成，可以提前结束循环。
在第二层循环中，我们通过比较相邻两个元素的值，如果前一个元素的值比后一个元素的值大，则交换这两个元素的位置，确保较大的元素在数组的右侧。
最后，在主函数中，我们定义一个整数数组，调用 bubbleSort 函数对数组进行排序，并输出排序后的结果。
冒泡排序算法的时间复杂度为 O(n^2)，不适用于大型数组。然而，由于它的代码实现相对简单，因此在小型数组的排序中仍然有一定的应用价值。
    
核心：
冒泡排序的核心是，对于遍历每一个i∈0~n-1，都遍历j∈0~n-i-1(写例子，i=0时j右界为n-1，i=1时j右界为n-2)。每一轮遍历i都将最大的数依次送到末尾，然后下一次遍历i，就处理前一个末尾（对应j的右界减小）。
    
void bubbleSort(int arr[], int size) {
  bool swapped = false;
  for (int i = 0; i < size - 1; i++) {
    swapped = false;
    for (int j = 0; j < size - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(arr[j], arr[j + 1]);
        swapped = true;
      }
    }
    if (swapped == false) {
      // 如果没有发生交换，则可以提前结束循环
      break;
    }
  }
}

int main() {
  int arr[] = {64, 34, 25, 12, 22, 11, 90};
  int size = sizeof(arr) / sizeof(arr[0]);
  bubbleSort(arr, size);
  // cout << "Sorted array: ";
  // for (int i = 0; i < size; i++)
  //   cout << arr[i] << " ";
  // cout << endl;
  return 0;
}
```

