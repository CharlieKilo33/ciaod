#pragma once

#include <utility>
#include <cstring>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;
using namespace std::literals;

struct CityInfo {
  int city_code;
  char city_name[10]{};
  char country[10]{};

  CityInfo(int code, const std::string& name, const std::string& country_name)
      : city_code(code) {
    std::strncpy(city_name, name.c_str(), sizeof(city_name));
    std::strncpy(country, country_name.c_str(), sizeof(country));
  }

  CityInfo() : city_code(0) {
    std::memset(city_name, 0, sizeof(city_name));
    std::memset(country, 0, sizeof(country));
  }
};

class BinaryFile {
 public:
  explicit BinaryFile(fs::path file_name) : file_name_(std::move(file_name)) {};
  static bool FileIsOpen(std::fstream &f);
  void ConvertTextToBinary();
  void SaveBinaryToText();
  void PrintAllRecords();
  void AccessRecordByNumber(int record_number);
  void DeleteRecordByKey(int key_value);
  void CreateCountryCodeTable(const std::string &country_name);
  void UpdateCityCodeByName(const std::string &city_name, int new_code);
  fs::path GetName();

 private:
  fs::path file_name_ = fs::path("E:/clion/ciaod/3/3_1.bin");
};
