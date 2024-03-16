#include "functions.h"

bool Functions::FileIsOpen(std::fstream& f){
  if(f.is_open()){
    return true;
  } else {
    std::cerr << "Error: file isn't opened!\n"s;
    return false;
  }
}

void Functions::GetFileInfo() {
  std::fstream fin;
  fin.open(file_name_, std::ios::in);
  if(!FileIsOpen(fin)){
    return;
  }
  std::string text;
  while(std::getline(fin, text)){
    std::cout << text << '\n';
  }
}

void Functions::AddText(){
  std::fstream fout;
  fout.open(file_name_, std::ios::out | std::ios::app);

  if(!FileIsOpen(fout)){
    return;
  }

  std::string text;
  std::cout << "Enter the text which you want to add: \n"s;
  std::cin >> text;

  fout << ' ' << text;
}
int Functions::GetNumberByIndex(int index) {
  std::fstream fin;
  fin.open(file_name_, std::ios::in);

  if(!FileIsOpen(fin)){
    return 0;
  }

  std::string str;
  for(int i = 0; std::getline(fin, str); ){
    for(char c : str){
      if(c != ' '){
        if(i == index){
          return c - '0';
        }
        ++i;
      }
    }

  }
  return 0;
}
