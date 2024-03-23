#include <iostream>
#include "HashTable.h"
#include "FunctionsBin.h"

void runSimpleTests() {
  // Тест 1: Проверка вставки и поиска элемента в хеш-таблице
  HashTable hashTable(FunctionsBin(__cxx11::path()));
  hashTable.insert(1, 0);
  hashTable.insert(101, 1);

  if (hashTable.find(1) == 0 && hashTable.find(101) == 1) {
    std::cout << "Test 1 Passed: Insertion and search functionality works correctly." << std::endl;
  } else {
    std::cout << "Test 1 Failed: Insertion and search functionality does not work correctly." << std::endl;
  }

  // Тест 2: Проверка удаления элемента из хеш-таблицы
  hashTable.remove(1);

  if (hashTable.find(1) == -1 && hashTable.find(101) == 1) {
    std::cout << "Test 2 Passed: Removal functionality works correctly." << std::endl;
  } else {
    std::cout << "Test 2 Failed: Removal functionality does not work correctly." << std::endl;
  }

  // Тест 3: Проверка взаимодействия хеш-таблицы с бинарным файлом
  // Загрузка данных из бинарного файла в хеш-таблицу
  std::ifstream binary_file_in(R"(E:\clion\ciaod\3\3_1.bin)", std::ios::binary);
  CityInfo city_info;
  int recordNumber = 0;
  while (binary_file_in.read(reinterpret_cast<char *>(&city_info), sizeof(CityInfo))) {
    hashTable.insert(city_info.city_code, recordNumber);
    recordNumber++;
  }
  binary_file_in.close();

  if (hashTable.find(1) == 0 && hashTable.find(101) == 1) {
    std::cout << "Test 3 Passed: Binary file interaction works correctly." << std::endl;
  } else {
    std::cout << "Test 3 Failed: Binary file interaction does not work correctly." << std::endl;
  }
}

int main() {
  runSimpleTests();

  return 0;
}