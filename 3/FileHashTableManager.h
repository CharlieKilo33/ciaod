#pragma once

#include "HashTable.h"
#include "BinaryFile.h"
#include <string>
#include <utility>

class FileHashTableManager {
 private:
  HashTable hash_table;
  BinaryFile binary_file_manager;

 public:
  explicit FileHashTableManager(const HashTable& table, BinaryFile binary_file_manager) : hash_table(table),
                                                                                   binary_file_manager(std::move(binary_file_manager)){};

  void ReadRecordFromFileAndInsertIntoTable();
  void DeleteRecordByKey(const int key);
  void FindRecordInFileByKey(int key);
};