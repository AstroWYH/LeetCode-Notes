![image](https://github.com/AstroWYH/LeetCode-Notes/assets/94472801/6171ed81-f773-45b4-986f-994dfd6d00fb)
```cpp
#include <Eigen/Core>
#include <Eigen/Eigen>
#include <chrono>
#include <iomanip>  // For setw
#include <iostream>
#include <typeinfo>
#include <unordered_set>
#include <vector>

#include "Eigen/Dense"
using namespace std;

#define START_LOG_TIME()                                  \
  std::chrono::high_resolution_clock::time_point t1 =     \
      std::chrono::high_resolution_clock::now();          \
  std::chrono::high_resolution_clock::time_point t2 = t1; \
  std::chrono::duration<double> time_used =               \
      std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
#define PRINT_COST_TIME(name)                                             \
  t2 = std::chrono::high_resolution_clock::now();                         \
  time_used =                                                             \
      std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1); \
  std::cout << std::fixed << name                                         \
            << " Time cost: " << (time_used.count() * 1000) << " ms."     \
            << std::endl;                                                 \
  t1 = t2;

template <typename T>
class DataManagerOrigin {
 public:
  typedef std::vector<T> DataType;
  typedef typename std::vector<T>::iterator DataTypeIterator;

  DataManagerOrigin() = default;

  ~DataManagerOrigin() = default;

  bool Init(const Eigen::Vector2i& size) {
    size_ = size;
    buffer_[0].resize(size_(0) * size_(1));
    buffer_[1].resize(size_(0) * size_(1));
    data_ = &buffer_[0];
    return true;
  }

  size_t size() const { return data_->size(); }

  T& at(size_t idx) { return data_->at(idx); }

  void Shift(const Eigen::Vector2i& offset) {
    const int32_t half_rows = static_cast<int32_t>(std::floor(size_(0) / 2));
    const int32_t half_cols = static_cast<int32_t>(std::floor(size_(1) / 2));
    // LOG_INFO << "wyh offset " << offset << " half_rows " << half_rows
    //          << " half_cols " << half_cols << " size_ " << size_;
    // offset 0 1 half_rows 150 half_cols 150 size_ 300 300
    if (abs(offset(0)) > half_rows || abs(offset(1)) > half_cols) {
      memset(data_->data(), 0, sizeof(T) * data_->size());
    }
    if (abs(offset(0)) >= 1 || abs(offset(1)) >= 1) {
      DataType* src = nullptr;
      DataType* dst = nullptr;
      if (data_ == &buffer_[0]) {
        src = &buffer_[0];
        dst = &buffer_[1];
      } else {
        src = &buffer_[1];
        dst = &buffer_[0];
      }
      data_ = dst;
      memset(data_->data(), 0, sizeof(T) * data_->size());
      Eigen::Vector2i start_src;
      Eigen::Vector2i end_src;
      start_src(0) = std::max(0, offset(0));                          // 1
      start_src(1) = std::max(0, offset(1));                          // 1
      end_src(0) = std::min(size_(0) - 1, size_(0) - 1 + offset(0));  // 2
      end_src(1) = std::min(size_(1) - 1, size_(1) - 1 + offset(1));  // 2
      if (start_src(0) > end_src(0) || start_src(1) > end_src(1)) {
        return;
      }
      const Eigen::Vector2i start_dst = start_src - offset;  // 0
      const Eigen::Vector2i end_dst = end_src - offset;      // 1
      const int col_length = end_src(1) - start_src(1) + 1;  // 2
      // LOG_INFO << "wyh start_src " << start_src << " end_src " << end_src
      //          << " start_dst " << start_dst << " end_dst " << end_dst
      //          << " col_length " << col_length << " offset " << offset
      //          << " size_ " << size_;
      // wyh start_src 0 1 end_src 299 299 start_dst 0 0 end_dst 299 298
      // col_length 299 offset 0 1 size_ 300 300
      for (int row = start_dst(0); row <= end_dst(0); ++row) {  // 0-1
        const int src_start_idx =
            (row + offset(0)) * size_(1) + start_src(1);          // 4 7
        const int dst_start_idx = row * size_(1) + start_dst(1);  // 0 3
        memcpy(&(dst->at(dst_start_idx)), &(src->at(src_start_idx)),
               sizeof(T) * col_length);
      }
    }
  }

  void Show(string str) {
    cout << str << "\n";
    for (int i = 0; i < size_(0); i++) {
      for (int j = size_(0) * i; j < size_(0) * i + size_(1); j++) {
        cout << setw(3) << data_->at(j) << " ";
      }
      cout << endl;
    }
  }

  void enqueue(const T& item) { data_->at(size_1d_++) = item; }

 private:
  DataType buffer_[2];
  DataType* data_ = nullptr;
  Eigen::Vector2i size_ = Eigen::Vector2i::Zero();
  int size_1d_ = 0;
};  // class DataManagerOrigin

template <typename T>
class DataManagerOpt {
 public:
  typedef std::vector<T> DataType;
  typedef typename std::vector<T>::iterator DataTypeIterator;

  DataManagerOpt() = default;

  ~DataManagerOpt() = default;

  bool Init(const Eigen::Vector2i& size) {
    size_ = size;
    buffer_.resize(size_(0) * size_(1));
    data_ = &buffer_;
    return true;
  }

  size_t size() const { return data_->size(); }

  T& at(size_t idx) { return data_->at((front_ + (int)idx) % data_->size()); }

  void Shift(const Eigen::Vector2i& offset) {
    const int32_t half_rows = static_cast<int32_t>(std::floor(size_(0) / 2));
    const int32_t half_cols = static_cast<int32_t>(std::floor(size_(1) / 2));
    // LOG_INFO << "wyh offset " << offset << " half_rows " << half_rows
    //          << " half_cols " << half_cols << " size_ " << size_;
    // offset 0 1 half_rows 150 half_cols 150 size_ 300 300
    if (abs(offset(0)) > half_rows || abs(offset(1)) > half_cols) {
      memset(data_->data(), 0, sizeof(T) * data_->size());
      return;
    }
    if (abs(offset(0)) >= 1 || abs(offset(1)) >= 1) {
      int new_front = front_ + offset(0) * size_(1) + offset(1);
      new_front = new_front >= 0 ? new_front : data_->size() - abs(new_front);
      front_ = new_front % data_->size();
      Eigen::Vector2i move_len;
      move_len(0) = size_(0) - abs(offset(0));
      move_len(1) = size_(1) - abs(offset(1));
      // cout << "move_len:\n" << move_len << endl;

      int protect_row_start = offset(0) > 0 ? 0 : abs(offset(0));
      int protect_row_stop = offset(0) > 0 ? move_len(0) - 1 : size_(0) - 1;
      int protect_col_start = offset(1) > 0 ? 0 : abs(offset(1));
      int protect_col_stop = offset(1) > 0 ? move_len(1) - 1 : size_(1) - 1;

      // cout << "protect_row_start " << protect_row_start << " protect_row_stop
      // "
      //      << protect_row_stop << " protect_col_start " << protect_col_start
      //      << " protect_col_stop " << protect_col_stop << endl;

      for (int i = 0; i < size_(0); i++) {
        for (int j = size_(0) * i; j < size_(0) * i + size_(1); j++) {
          int row = i;
          int col = j - (size_(0) * i);
          if (protect_row_start <= row && row <= protect_row_stop &&
              protect_col_start <= col && col <= protect_col_stop) {
            continue;
          }
          at(j) = 0;
        }
      }
    }
  }

  void Show(string str) {
    cout << str << "\n";
    for (int i = 0; i < size_(0); i++) {
      for (int j = size_(0) * i; j < size_(0) * i + size_(1); j++) {
        cout << setw(3) << at(j) << " ";
      }
      cout << endl;
    }
  }

  void enqueue(const T& item) {
    if (size_1d_ < data_->size()) {
      size_1d_++;
      data_->at((front_ + size_1d_ - 1) % data_->size()) = item;
    }
  }

 private:
  DataType buffer_;
  DataType* data_ = nullptr;
  Eigen::Vector2i size_ = Eigen::Vector2i::Zero();
  int front_ = 0;
  int size_1d_ = 0;
};  // class DataManagerOpt

int main() {
  const int kShiftTimes = 1;
  // const int kShiftTimes = 2;
  // const int kShiftTimes = 3;

  // Eigen::Vector2i size(5, 5);
  Eigen::Vector2i size(15, 15);
  // Eigen::Vector2i offset(2, 2);
  Eigen::Vector2i offset(1, -2);

  {
    DataManagerOrigin<int> layer_content;
    layer_content.Init(size);

    for (int i = 0; i < size(0) * size(1); ++i) {
      layer_content.enqueue(i + 1);
    }
    layer_content.Show("DataManagerOrigin Data:");

    {
      START_LOG_TIME()
      for (int i = 0; i < kShiftTimes; i++) {
        layer_content.Shift(offset);
        layer_content.Show("DataManagerOrigin Shift:");
      }
      PRINT_COST_TIME("DataManagerOrigin");
    }
  }
  {
    DataManagerOpt<int> layer_content;
    layer_content.Init(size);

    for (int i = 0; i < size(0) * size(1); ++i) {
      layer_content.enqueue(i + 1);
    }
    layer_content.Show("DataManagerOpt Data:");

    {
      START_LOG_TIME()
      for (int i = 0; i < kShiftTimes; i++) {
        layer_content.Shift(offset);
        layer_content.Show("DataManagerOpt Shift:");
      }
      PRINT_COST_TIME("DataManagerOpt");
    }
  }
  return 0;
}
```


