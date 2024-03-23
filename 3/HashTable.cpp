#include "HashTable.h"

#include <utility>


HashTable::HashTable(FunctionsBin bin_functions) : bin_functions(std::move(bin_functions)) {
  for (auto & i : table) {
    i = nullptr;
  }
}

HashTable::~HashTable() {
  for (auto & i : table) {
    i = nullptr;
  }
}

int HashTable::HashFunction(int key) {
  return key % TABLE_SIZE;
}

void HashTable::Insert(int key, const CityInfo& city_info) {
  int index = HashFunction(key);
  std::unique_ptr<Node> newNode = std::make_unique<Node>(key, city_info);
  newNode->next = std::move(table[index]);
  table[index] = std::move(newNode);
}

void HashTable::Delete(int key) {
  int index = HashFunction(key);
  Node* current = table[index].get();
  std::unique_ptr<Node> prev = nullptr;

  while (current != nullptr) {
    if (current->key == key) {
      if (prev != nullptr) {
        prev->next = std::move(current->next); // Обновляем указатель предыдущего узла
      } else {
        table[index] = std::move(current->next); // Удаляем первый узел в списке
      }
      std::cout << "Key " << key << " deleted." << std::endl;
      return;
    }
    prev = std::move(std::unique_ptr<Node>(current)); // Преобразуем указатель current в уникальный указатель
    current = current->next.get();
  }

  std::cout << "Key not found for deletion." << std::endl;
}

void HashTable::Search(int key) {
  int index = HashFunction(key);
  Node* current = table[index].get();

  while (current != nullptr) {
    if (current->key == key) {
      std::cout << "Key found - City Code: " << current->city_info.city_code << ", City Name: "
                << current->city_info.city_name << ", Country: " << current->city_info.country << std::endl;
      return;
    }
    current = current->next.get();
  }

  std::cout << "Key not found." << std::endl;
}

void HashTable::LoadDataFromBinaryFile(const std::string& file_name) {
  std::fstream binary_file(file_name, std::ios::binary | std::ios::in);

  if (!FunctionsBin::FileIsOpen(binary_file)) {
    return;
  }

  CityInfo city_info;
  while (binary_file.read(reinterpret_cast<char *>(&city_info), sizeof(CityInfo))) {
    Insert(city_info.city_code, city_info);
  }

  binary_file.close();
}