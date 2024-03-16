#include <iostream>
#include <iostream>
#include <iomanip>
#include <bitset>
#include <vector>
#include <chrono>

using namespace std;

void task_1() {
  int value = 0x0;

  std::cout << "Number: " << bitset<sizeof(int) * 8>(value) << std::endl;

  int bit1 = 12;
  int bit2 = 14;
  int bit3 = 3;

  int mask1 = 1 << bit1;
  int mask2 = 1 << bit2;
  int mask3 = 1 << bit3;

  value |= mask1;
  value |= mask2;
  value |= mask3;

  std::cout << "Result: " << bitset<sizeof(int) * 8>(value) << std::endl;
}

void task_2() {
  int value;

  std::cout << "Enter the number: \n";
  std::cin >> value;

  std::cout << "Number: " << bitset<sizeof(int) * 8>(value) << std::endl;

  for (int i = 0; i < sizeof(int) * 8; i++) {
    if (i % 2 != 0) {
      int mask = ~(1 << i);
      value &= mask;
    }
  }

  std::cout << "Result: " << bitset<sizeof(int) * 8>(value) << std::endl;
}

void task_3() {
  int value;

  std::cout << "Enter the number: \n";
  std::cin >> value;

  value = value << 9;

  std::cout << "Result: " << bitset<sizeof(int) * 8>(value) << std::endl;
  std::cout << "Result in dec: " << value << std::endl;
}

void task_4(){
  int value;

  std::cout << "Enter the number: \n";
  std::cin >> value;

  value = value >> 9;

  std::cout << "Result: " << bitset<sizeof(int) * 8>(value) << std::endl;
  std::cout << "Result in dec: " << value << std::endl;
}

void task_5(){
  int value;
  int mask;
  int n;

  std::cout << "Enter the number: ";
  std::cin >> value;

  std::cout << "Enter the bit position (0-31): ";
  std::cin >> n;

  mask = 1 << n; // Создаем маску, у которой только n-й бит установлен в 1
  value = value | mask; // Устанавливаем n-й бит в 1 с помощью операции побитового ИЛИ

  std::cout << "Result: " << bitset<sizeof(int) * 8>(value) << std::endl;
  std::cout << "Result in dec: " << value << std::endl;
}

unsigned char* create_array(size_t size) {
  unsigned char* numbers = new unsigned char[(size >> 3) + 1];
  for (size_t i = 0; i <= (size >> 3); ++i) {
    numbers[i] = 0;
  }

  return numbers;
}

void sort_array(unsigned char* &numbers, vector<int>input_nums) {
  for (size_t i = 0; i < input_nums.size(); ++i) {
    numbers[input_nums[i] >> 3] = numbers[input_nums[i] >> 3] | (1 << (input_nums[i] & 7));
  }
}

void get_nums(unsigned char* numbers, vector<int> &output_nums) {
  output_nums.clear();
  unsigned char mask = 1;
  size_t bit;

  for (size_t i = 0; i <= 10000000 >> 3; ++i) {
    bit = 0;
    while (numbers[i] != 0) {
      if ((numbers[i] & mask) != 0) {
        output_nums.push_back((i << 3) + bit);
      }
      numbers[i] >>= 1;
      ++bit;
    }
  }
}

void array_bit_sort() {
  size_t average;
  cout << "How many unique numbers we need sort?   ";
  cin >> average;

  vector<int> input_nums(average);
  cout << "Enter numbers to sort:" << endl;
  for (size_t i = 0; i < average; ++i) {
    cin >> input_nums[i];
  }

  auto start = chrono::high_resolution_clock::now();
  unsigned char* numbers = create_array(10000000);
  sort_array(numbers, input_nums);
  get_nums(numbers, input_nums);
  auto end = chrono::high_resolution_clock::now();

  cout << "--------------------------SORTED--------------------------" << endl;
  for (int num : input_nums) {
    cout << num << " ";
  }

  chrono::duration<float> duration = end - start;
  cout << endl << "Time: " << setprecision(4) << duration.count();

  delete[] numbers;
}

void bit_sort() {
  size_t average, num, size = 9000000;
  cout << "How many unique numbers we need sort?   ";
  cin >> average;

  vector<bool> numbers(size);
  vector<int> input_nums;
  cout << "Enter numbers to sort:" << endl;
  for (size_t i = 0; i < average; ++i) {
    cin >> num;
    input_nums.push_back(num - 1000000);
  }

  auto start = chrono::high_resolution_clock::now();
  for (size_t i = 0; i < average; ++i) {
    numbers[input_nums[i]] = true;
  }
  auto end = chrono::high_resolution_clock::now();

  cout << "Sorted:" << endl;
  for (size_t i = 0; i < size; ++i) {
    if (numbers[i]) {
      cout << i + 1000000 << endl;
    }
  }

  chrono::duration<float> duration = end - start;
  cout << endl << "Time: " << setprecision(4) << duration.count();
}

int main() {
  array_bit_sort();
}