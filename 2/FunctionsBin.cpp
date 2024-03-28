#include "FunctionsBin.h"

bool BinaryFile::FileIsOpen(std::fstream &f) {
  if (f.is_open()) {
    return true;
  } else {
    std::cerr << "Error: file isn't opened!\n"s;
    return false;
  }
}

void BinaryFile::ConvertTextToBinary() {
  std::fstream text_file_fin(file_name_.replace_extension(".txt"), std::ios::in);
  if (!FileIsOpen(text_file_fin)) {
    return;
  }

  std::fstream binary_file_fout(file_name_.replace_extension(".bin"), std::ios::binary | std::ios::out);
  if (!FileIsOpen(binary_file_fout)) {
    return;
  }

  CityInfo city_info;
  while (text_file_fin >> city_info.city_code >> city_info.city_name >> city_info.country) {
    binary_file_fout.write(reinterpret_cast<char *>(&city_info), sizeof(CityInfo));
  }

  text_file_fin.close();
  binary_file_fout.close();
}

void BinaryFile::SaveBinaryToText() {
  std::fstream binary_file_fin(file_name_.replace_extension(".bin"), std::ios::binary | std::ios::in);
  if (!FileIsOpen(binary_file_fin)) {
    return;
  }

  std::fstream text_file_fout(file_name_.replace_extension(".txt"), std::ios::out);
  if (!FileIsOpen(text_file_fout)) {
    return;
  }

  CityInfo city_info;
  while (binary_file_fin.read(reinterpret_cast<char *>(&city_info), sizeof(CityInfo))) {
    text_file_fout << city_info.city_code << " " << city_info.city_name << " " << city_info.country << "\n";
  }

  binary_file_fin.close();
  text_file_fout.close();
}

void BinaryFile::PrintAllRecords() {
  std::fstream binary_file_fin(file_name_.replace_extension(".bin"), std::ios::binary | std::ios::in);

  if (!FileIsOpen(binary_file_fin)) {
    return;
  }

  CityInfo city_info;
  while (binary_file_fin.read(reinterpret_cast<char *>(&city_info), sizeof(CityInfo))) {
    std::cout << "City Code: " << city_info.city_code << ", City Name: " << city_info.city_name << ", Country: "
              << city_info.country << std::endl;
  }

  binary_file_fin.close();
}

void BinaryFile::AccessRecordByNumber(int record_number) {
  std::fstream binary_file_fin(file_name_.replace_extension(".bin"), std::ios::binary | std::ios::in);

  if (!FileIsOpen(binary_file_fin)) {
    return;
  }

  CityInfo city_info;
  while (binary_file_fin.read(reinterpret_cast<char *>(&city_info), sizeof(CityInfo))) {
    std::stringstream ss;
    ss << city_info.city_code;
    std::string city_code_str = ss.str();

    city_code_str.erase(std::remove_if(city_code_str.begin(), city_code_str.end(), ::isspace), city_code_str.end());

    if (std::stoi(city_code_str) == record_number) {
      std::cout << "Record found - " << "City Code: " << city_info.city_code << ", City Name: " << city_info.city_name
                << ", Country: " << city_info.country << std::endl;
      binary_file_fin.close();
      return;
    }
  }

  binary_file_fin.close();
}

void BinaryFile::DeleteRecordByKey(int key_value) {
  std::fstream binary_file_fin(file_name_, std::ios::binary | std::ios::in | std::ios::out);
  if (!FileIsOpen(binary_file_fin)) {
    return;
  }

  CityInfo city_info;
  std::streampos current_pos;
  std::streampos next_pos;

  while (binary_file_fin.read(reinterpret_cast<char *>(&city_info), sizeof(CityInfo))) {
    if (city_info.city_code == key_value) {
      // Сохраняем текущую позицию для перезаписи после удаления
      current_pos = binary_file_fin.tellg();
      break;
    }
  }

  if (binary_file_fin.eof()) {
    std::cout << "Record not found for deletion." << std::endl;
    binary_file_fin.close();
    return;
  }

  // Перемещаем указатель чтения/записи в начало записи для удаления
  binary_file_fin.seekp(std::streamoff(current_pos) - sizeof(CityInfo));

  // Создаем пустую запись для перезаписи удаленной записи
  CityInfo empty_city_info;
  binary_file_fin.write(reinterpret_cast<char *>(&empty_city_info), sizeof(CityInfo));

  // Сдвигаем указатель чтения/записи на место после удаленной записи
  binary_file_fin.seekg(current_pos);

  // Переписываем оставшиеся записи в файле
  while (binary_file_fin.read(reinterpret_cast<char *>(&city_info), sizeof(CityInfo))) {
    next_pos = binary_file_fin.tellg();
    binary_file_fin.seekp(std::streamoff(current_pos) - sizeof(CityInfo));
    binary_file_fin.write(reinterpret_cast<char *>(&city_info), sizeof(CityInfo));
    current_pos = next_pos;
  }

  binary_file_fin.seekp(0, std::ios::end);

// Получаем текущую позицию указателя
  std::streampos end_pos = binary_file_fin.tellp();

// Устанавливаем указатель на позицию после последней записи
  binary_file_fin.seekp(std::streamoff(end_pos) - sizeof(CityInfo));

// Определяем размер файла после удаления
  std::streampos new_end_pos = binary_file_fin.tellp();

// Обрезаем файл до нового конечного размера
  binary_file_fin.seekp(new_end_pos);

  std::cout << "Record with key " << key_value << " deleted successfully." << std::endl;

  binary_file_fin.close();
}

void BinaryFile::CreateCountryCodeTable(const std::string &country_name) {
  std::fstream binary_file_fin(file_name_, std::ios::binary | std::ios::in);
  if (!FileIsOpen(binary_file_fin)) {
    return;
  }

  fs::path file_path = fs::path("C:/Users/misha/CLionProjects/ciaod/2/") / fs::path(country_name + "_codes.txt");
  std::fstream country_table_fout(file_path, std::ios::out);
  if (!FileIsOpen(country_table_fout)) {
    return;
  }

  CityInfo city_info;
  while (binary_file_fin.read(reinterpret_cast<char *>(&city_info), sizeof(CityInfo))) {
    if (std::string(city_info.country) == country_name) {
      country_table_fout << "City Code: " << city_info.city_code << ", City Name: " << city_info.city_name << std::endl;
    }
  }

  binary_file_fin.close();
  country_table_fout.close();
}

void BinaryFile::UpdateCityCodeByName(const std::string &city_name, int new_code) {
  std::fstream binary_file(file_name_, std::ios::in | std::ios::out | std::ios::binary);
  if (!FileIsOpen(binary_file)) {
    return;
  }

  CityInfo city_info;
  while (binary_file.read(reinterpret_cast<char *>(&city_info), sizeof(CityInfo))) {
    if (std::string(city_info.city_name) == city_name) {
      city_info.city_code = new_code;
      binary_file.seekp(-static_cast<int>(sizeof(CityInfo)), std::ios::cur);
      binary_file.write(reinterpret_cast<char *>(&city_info), sizeof(CityInfo));
      break;
    }
  }

  binary_file.close();
}