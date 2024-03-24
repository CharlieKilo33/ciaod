#include <iostream>
#include "HashTable.h"

//void test_insert_and_find() {
//  HashTable table;
//  insert_key(table, "key1", 10);
//  insert_key(table, "key2", 20);
//
//  if (find_key(table, "key1")->position == 10)
//    std::cout << "Test Insert and Find 1 Passed" << std::endl;
//  else
//    std::cout << "Test Insert and Find 1 Failed" << std::endl;
//
//  if (find_key(table, "key2")->position == 20)
//    std::cout << "Test Insert and Find 2 Passed" << std::endl;
//  else
//    std::cout << "Test Insert and Find 2 Failed" << std::endl;
//}
//
//void test_delete() {
//  HashTable table;
//  insert_key(table, "key1", 10);
//  insert_key(table, "key2", 20);
//
//  delete_key(table, "key1");
//
//  if (find_key(table, "key1") == nullptr)
//    std::cout << "Test Delete Passed" << std::endl;
//  else
//    std::cout << "Test Delete Failed" << std::endl;
//}

void test_rehash() {
  HashTable table;
  // Insert enough keys to trigger rehash
  for (int i = 0; i < 1000; ++i) {
    insert_key(table,"key" + std::to_string(i), i);
  }

  printHashTable(table);
}

int main() {
//  test_insert_and_find();
//  test_delete();
  test_rehash();

  return 0;
}