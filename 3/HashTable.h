#include "FunctionsBin.h"
#include <iostream>
#include <string>
#include <memory>

class HashTable {
 private:
  struct Node {
    int key;
    CityInfo city_info;
    std::unique_ptr<Node> next;

    Node(int k, const CityInfo& info) : key(k), city_info(info), next(nullptr) {}
  };

  static const int TABLE_SIZE = 10;
  std::unique_ptr<Node> table[TABLE_SIZE];
  FunctionsBin bin_functions;

  static int HashFunction(int key);

 public:
  explicit HashTable(FunctionsBin bin_functions);
  ~HashTable();

  void Insert(int key, const CityInfo& city_info);
  void Delete(int key);
  void Search(int key);
  void LoadDataFromBinaryFile(const std::string& file_name);
};