#include "HashTable.h"
#include <functional>

size_t hash_key(const string& key, size_t size) {
  hash<string> hash_fn;
  return hash_fn(key) % size;
}

bool insert_key(HashTable &table, const string& key, int position) {
  size_t index = hash_key(key, table.size);
  Node* new_node = new Node(key, position);

  if (!table.records[index]) {
    table.records[index] = new_node;
  } else {
    Node* current = table.records[index];
    while (current->next) {
      current = current->next;
    }
    current->next = new_node;
  }

  table.filled++;
  return true;
}

Node* find_key(HashTable &table, const string& key) {
  size_t index = hash_key(key, table.size);
  Node* current = table.records[index];

  while (current) {
    if (current->key == key) {
      return current;
    }
    current = current->next;
  }

  return nullptr;
}

int get_index(HashTable &table, const string& key) {
  size_t index = hash_key(key, table.size);
  Node* current = table.records[index];

  while (current) {
    if (current->key == key) {
      return index;
    }
    current = current->next;
  }

  return -1;
}

int delete_key(HashTable &table, const string& key) {
  size_t index = hash_key(key, table.size);
  Node* current = table.records[index];
  Node* prev = nullptr;

  while (current) {
    if (current->key == key) {
      if (prev) {
        prev->next = current->next;
      } else {
        table.records[index] = current->next;
      }
      table.filled--;
      delete current;
      return index;
    }
    prev = current;
    current = current->next;
  }

  return -1;
}

void rehash(HashTable &table) {
  size_t new_size = table.size * 2;
  vector<Node*> new_records(new_size);

  for (size_t i = 0; i < table.size; ++i) {
    Node* current = table.records[i];
    while (current) {
      size_t new_index = hash_key(current->key, new_size);

      Node* temp = current->next;
      current->next = new_records[new_index];
      new_records[new_index] = table.records[i];
      table.records[i] = temp;

      current = table.records[i];
    }
  }

  table.size = new_size;
  table.records = new_records;
}

void printHashTable(const HashTable &table) {
  for (size_t i = 0; i < table.size; ++i) {
    cout << "Index " << i << ": ";
    Node* current = table.records[i];
    while (current) {
      cout << "(" << current->key << ", " << current->position << ") ";
      current = current->next;
    }
    cout << endl;
  }
}

int testHashT() {
  // Implement testing logic here
  return 0;
}
HashTable::~HashTable() {
  for (size_t i = 0; i < size; ++i) {
    Node* current = records[i];
    while (current) {
      Node* temp = current;
      current = current->next;
      delete temp;
    }
  }
}