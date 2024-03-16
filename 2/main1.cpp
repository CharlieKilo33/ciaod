#include "functions.h"

int main(){
  std::cout << "Enter the file's name:\n";
  std::string temp;
  std::cin >> temp;
  fs::path file_path = fs::path("E:/clion/ciaod/2/") / fs::path(temp + ".txt");

  Functions file_reader(file_path);
  std::cout << file_reader.GetNumberByIndex(7);
}