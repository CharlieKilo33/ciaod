#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;
using namespace std::literals;

class FunctionsDefault {
 public:
  explicit FunctionsDefault(fs::path file_name) : file_name_(std::move(file_name)) {};
  static bool FileIsOpen(std::fstream &f);
  void GetFileInfo();
  void AddText();
  int GetNumberByIndex(int index);
  int GetNumbersCount();
  void CreateNewFile();

 private:
  fs::path file_name_;
  std::pair<int, int> GetMinMaxNumbers();
};


