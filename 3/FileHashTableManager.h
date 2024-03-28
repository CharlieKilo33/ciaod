#pragma once

#include <string>
#include <utility>

#include "BinaryFile.h"
#include "HashTable.h"

void ReadRecordFromFileAndInsertIntoTable(HashTable& hash_table);
void DeleteRecordByKey(const int key);
void FindRecordInFileByKey(int key);