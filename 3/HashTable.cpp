#include "HashTable.h"
#include <functional>

size_t hash_key(const string& key, size_t size) {
  hash<string> hash_fn;
  return hash_fn(key) % size;
}

bool insert_key(HashTable &table, const string& key, int position) {
  size_t index = hash_key(key, table.size);
  unique_ptr<Node> new_node = make_unique<Node>(key, position);

  if (!table.records[index]) {
    table.records[index] = std::move(new_node);
  } else {
    Node* current = table.records[index].get();
    while (current->next) {
      current = current->next.get();
    }
    current->next = std::move(new_node);
  }

  table.filled++;
  return true;
}

Node* find_key(HashTable &table, const string& key) {
  size_t index = hash_key(key, table.size);
  Node* current = table.records[index].get();

  while (current) {
    if (current->key == key) {
      return current;
    }
    current = current->next.get();
  }

  return nullptr;
}

int get_index(HashTable &table, const string& key) {
  size_t index = hash_key(key, table.size);
  Node* current = table.records[index].get();

  while (current) {
    if (current->key == key) {
      return index;
    }
    current = current->next.get();
  }

  return -1;
}

int delete_key(HashTable &table, const string& key) {
  size_t index = hash_key(key, table.size);
  Node* current = table.records[index].get();
  Node* prev = nullptr;

  while (current) {
    if (current->key == key) {
      if (prev) {
        prev->next = std::move(current->next);
      } else {
        table.records[index] = std::move(current->next);
      }
      table.filled--;
      return index;
    }
    prev = current;
    current = current->next.get();
  }

  return -1;
}

void rehash(HashTable &table) {
  size_t new_size = table.size * 2;
  vector<unique_ptr<Node>> new_records(new_size);

  for (size_t i = 0; i < table.size; ++i) {
    Node* current = table.records[i].get();
    while (current) {
      size_t new_index = hash_key(current->key, new_size);

      unique_ptr<Node> temp = std::move(current->next);
      current->next = std::move(new_records[new_index]);
      new_records[new_index] = std::move(table.records[i]);
      table.records[i] = std::move(temp);

      current = table.records[i].get();
    }
  }

  table.size = new_size;
  table.records = std::move(new_records);
}

void printHashTable(const HashTable &table) {
  for (size_t i = 0; i < table.size; ++i) {
    cout << "Index " << i << ": ";
    Node* current = table.records[i].get();
    while (current) {
      cout << "(" << current->key << ", " << current->position << ") ";
      current = current->next.get();
    }
    cout << endl;
  }
}

int testHashT() {
  // Implement testing logic here
  return 0;
}
HashTable::~HashTable() = default;
