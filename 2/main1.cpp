#include "FunctionsDefault.h"
#include "FunctionsBin.h"

int main() {
  std::cout << "Enter the file's name:\n";
  std::string temp;
  std::cin >> temp;
  fs::path file_path = fs::path("E:/clion/ciaod/2/") / fs::path(temp + ".txt");

//  FunctionsDefault file_reader(file_path);
//  file_reader.CreateNewFile();
  FunctionsBin file_reader(file_path);
  file_reader.ConvertTextToBinary();
  file_reader.PrintAllRecords();
  file_reader.AccessRecordByNumber(5327);
  std::cout << '\n';
  file_reader.UpdateCityCodeByName("Mmmmoscow", 1488);
  file_reader.PrintAllRecords();
}