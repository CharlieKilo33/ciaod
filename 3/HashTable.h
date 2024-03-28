#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <utility>
#include <vector>
using namespace std;

struct Node {
  string key;
  int position;
  bool is_deleted;
  Node* next;

  Node() : position(-1), is_deleted(false), next(nullptr) {};
  Node(string _key, int _position) : key(std::move(_key)), position(_position), is_deleted(false), next(nullptr) {};
};

struct HashTable {
  size_t size;
  size_t filled;
  std::vector<Node*> records;

  explicit HashTable(size_t _size = 10) : size(_size), filled(0) {
    records.reserve(size);
    for (size_t i = 0; i < size; ++i) {
      records.push_back(new Node());
    }
  }
  ~HashTable();
};

size_t hash_key(const string& key, size_t size);
bool insert_key(HashTable &table, const string& key, int position);
Node* find_key(HashTable &table, const string& key);
int get_index(HashTable &table, const string& key);
int delete_key(HashTable &table, const string& key);
void rehash(HashTable &table);
void printHashTable(const HashTable &table);
int testHashT();