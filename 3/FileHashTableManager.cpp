//#include "FileHashTableManager.h"
//
//void FileHashTableManager::ReadRecordFromFileAndInsertIntoTable() {
//  // Open the binary file
//
//
//  // Read records from the binary file and insert them into the hash table
//  CityInfo city_info;
//  while (file.read(reinterpret_cast<char*>(&city_info), sizeof(CityInfo))) {
//    insert_key(hash_table, std::to_string(city_info.city_code), file.tellg());
//  }
//
//  file.close();
//}
//
//void FileHashTableManager::DeleteRecordByKey(const int key) {
//  // Find the record in the hash table
//  int record_position = hash_table.find_key(std::to_string(key));
//  if (record_position == -1) {
//    std::cerr << "Error: Record with key " << key << " not found in the hash table." << std::endl;
//    return;
//  }
//
//  // Open the binary file for deletion
//  std::fstream file(binary_file_manager.getFileName(), std::ios::in | std::ios::out | std::ios::binary);
//  if (!file.is_open()) {
//    std::cerr << "Error: Could not open file for deletion." << std::endl;
//    return;
//  }
//
//  // Move to the record position and mark it as deleted
//  file.seekp(record_position);
//  CityInfo empty_info;
//  file.write(reinterpret_cast<char*>(&empty_info), sizeof(CityInfo));
//
//  file.close();
//}
//
//void FileHashTableManager::FindRecordInFileByKey(int key) {
//  // Find the record position in the hash table
//  int record_position = hash_table.find_key(std::to_string(key));
//  if (record_position == -1) {
//    std::cerr << "Error: Record with key " << key << " not found in the hash table." << std::endl;
//    return;
//  }
//
//  // Access the record in the binary file by record position
//  binary_file_manager.AccessRecordByNumber(record_position);
//}
//
