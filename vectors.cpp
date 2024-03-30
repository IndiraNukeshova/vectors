#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

class ranges {
  using pointer = int *;
  pointer _data;
  int start; // a
  int end;   // b
  int step;  // s
public:
  ranges(int b) : start(0), end(b), step(1) {

    std::cout << "constructor with one parametr\n";
    _data = new int[end];
  }

  ranges(int a, int b) : start(a), end(b), step(1) {
    std::cout << "constructor with two parametrs\n";
    _data = new int[end - start + 1];
  }

  ranges(int a, int b, int d) : start(a), end(b), step(d) {
    std::cout << "constructor with three parametrs\n";
    _data = new int[(end - start) / step];
  }

  ranges(const std::initializer_list<int> &values) : end(values.size()) {
    std::cout << "Brace-initialize constructor\n";
    if (end > 0) {
      _data = new int[end];
      std::copy(values.begin(), values.end(), _data);
    } else
      _data = nullptr;
  }

  ranges(const ranges &other)
      : start(other.start), end(other.end), step(other.step) {
    std::cout << "Copy constructor\n";
    if (end != 0) {
      _data = new int[(end - start) / step];
      for (int i = 0; i < end; i++)
        _data[i] = other._data[i];
    } else
      _data = nullptr;
  }
  ranges(ranges &&other)
      : start(other.start), end(other.end), step(other.step) {
    std::cout << "Move constructor\n";
    _data = other._data;
    other.end = 0;
    other._data = nullptr;
  }

  ranges &operator=(const ranges &other) {
    std::cout << "Copy assignment\n";
    start = other.start;
    end = other.end;
    step = other.step;

    if (end != 0) {
      _data = new int[(end - start) / step];
      for (int i = start; i < end; i += step)
        _data[i] = other._data[i];
    } else
      _data = nullptr;
    return *this;
  }
  ranges &operator=(ranges &&other) {
    std::cout << "Move assignment\n";
    start = other.start;
    end = other.end;
    step = other.step;
    _data = other._data;
    other.end = 0;
    other._data = nullptr;

    return *this;
  }

  std::vector<int> to_vector() const {
    std::vector<int> result;
    for (int i = start; i < end; i = i + step) {
      result.push_back(i);
    }
    return result;
  }
};
void print(std::vector<int> const &input) {
  std::copy(input.begin(), input.end(),
            std::ostream_iterator<int>(std::cout, " "));
};
int main() {
  ranges r1(7);
  ranges r2 = r1;
  ranges r3 = ranges(2, 7);
  ranges r4 = std::move(r1);
  ranges &&r5 = ranges(1, 10, 2);
  ranges r6{27, 0, 39, 26};

  std::cout << "\n";

  std::vector<int> v1 = r1.to_vector(); // v1 содержит {0, 1, 2, 3, 4, 5, 6}
  print(v1);
  std::cout << "\n";
  std::vector<int> v2 = r2.to_vector(); // v2 содержит {0, 1, 2, 3, 4, 5, 6}
  print(v2);
  std::cout << "\n";
  std::vector<int> v3 = r3.to_vector(); // v содержит {2, 3, 4, 5, 6}
  print(v3);
  std::cout << "\n";
  std::vector<int> v4 = r4.to_vector(); // v содержит {0, 1, 2, 3, 4, 5, 6}
  print(v4);
  std::cout << "\n";
  std::vector<int> v5 = r5.to_vector(); // v5 содержит {1, 3, 5, 7, 9}
  print(v5);
  std::cout << "\n";
}
