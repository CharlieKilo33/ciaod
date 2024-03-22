#include "FunctionsDefault.h"

bool FunctionsDefault::FileIsOpen(std::fstream &f) {
  if (f.is_open()) {
    return true;
  } else {
    std::cerr << "Error: file isn't opened!\n"s;
    return false;
  }
}

void FunctionsDefault::GetFileInfo() {
  std::fstream fin;
  fin.open(file_name_, std::ios::in);

  if (!FileIsOpen(fin)) {
    return;
  }

  std::string text;
  while (std::getline(fin, text)) {
    std::cout << text << '\n';
  }
  fin.close();
}

void FunctionsDefault::AddText() {
  std::fstream fout;
  fout.open(file_name_, std::ios::out | std::ios::app);

  if (!FileIsOpen(fout)) {
    return;
  }

  std::string text;
  std::cout << "Enter the text which you want to add: \n"s;
  std::getline(std::cin, text);

  fout << ' ' << text;
  fout.close();
}

int FunctionsDefault::GetNumberByIndex(int index) {
  std::fstream fin;
  fin.open(file_name_, std::ios::in);

  if (!FileIsOpen(fin)) {
    return 0;
  }

  int num;
  int current_index = 0;
  while (fin >> num) {
    if (current_index == index) {
      fin.close();
      return num;
    }
    ++current_index;
  }

  fin.close();
  return 0;
}

int FunctionsDefault::GetNumbersCount() {
  std::fstream fin;
  fin.open(file_name_, std::ios::in);

  if (!FileIsOpen(fin)) {
    return 0;
  }

  int count = 0;
  int num;
  while (fin >> num) {
    ++count;
  }

  fin.close();
  return count;
}

std::pair<int, int> FunctionsDefault::GetMinMaxNumbers() {
  std::fstream fin;
  fin.open(file_name_, std::ios::in);

  if (!FileIsOpen(fin)) {
    return {};
  }

  int min = std::numeric_limits<int>::max();
  int max = std::numeric_limits<int>::min();
  int num;
  while (fin >> num) {
    if (num < min) {
      min = num;
    }
    if (num > max) {
      max = num;
    }
  }

  fin.close();
  return {min, max};
}

void FunctionsDefault::CreateNewFile() {
  std::fstream fin, fout;
  fin.open(file_name_, std::ios::in);

  if (!FileIsOpen(fin)) {
    return;
  }

  std::cout << "Enter the new file's name:\n";
  std::string temp;
  std::cin >> temp;
  fs::path second_file_name = fs::path("E:/clion/ciaod/2/") / fs::path(temp + ".txt");
  fout.open(second_file_name, std::ios::out);

  if (!FileIsOpen(fout)) {
    return;
  }

  std::pair<int, int> min_max_numbers = GetMinMaxNumbers();
  int num;
  while (fin >> num) {
    num += min_max_numbers.first + min_max_numbers.second;
    fout << num;

    char next_char = static_cast<char>(fin.peek());
    if (next_char == '\n') {
      fout << std::endl;
    } else {
      fout << " ";
    }
  }

  fout.close();
  fin.close();
}