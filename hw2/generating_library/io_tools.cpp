#include<string>
#include<vector>
#include<iostream>
#include<io_tools.h>
#include<sstream>

namespace igg {
namespace io_tools{

void SetToDimensions(std::stringstream& my_sstream, ImageData& image_data){
  my_sstream >> image_data.rows >> image_data.cols;
  int vector_size{ image_data.rows * image_data.cols };
  image_data.data.reserve(vector_size);
}

void SetToMaxVal(std::stringstream& my_sstream, ImageData& image_data){
  my_sstream >> image_data.max_val;
}

void SetToData(std::stringstream& my_sstream, ImageData& image_data) {
  int temp;
  while (my_sstream >> temp) {
    image_data.data.push_back(temp);
  }
}


ImageData ReadFromPgm(const std::string& file_name){
  int sentinel{ -1 };

  ImageData image_data;  
  image_data.rows = sentinel;
  image_data.cols = sentinel;
  image_data.max_val = sentinel; 

  std::ifstream my_input(file_name);
  std::string line;
  while (std::getline(my_input, line)) { // read each line into the string line
    
    int first_char{ std::tolower(line[0]) }; 
    if (first_char == '#') continue;  // Don't care about comment lines
    if (first_char == 'p') continue;  // Don't care about first line - maybe add functionality
    
    std::stringstream my_sstream{line}; 

    if (image_data.rows == sentinel && image_data.cols == sentinel) { 
      SetToDimensions(my_sstream, image_data);
    } else if (image_data.max_val == sentinel) {
      SetToMaxVal(my_sstream, image_data);
    } else {
      SetToData(my_sstream, image_data);
    } // endif

  }
  return image_data;
}

bool WriteToPgm(const ImageData& image_data, const std::string& file_name){
  std::ofstream output(file_name, std::ios::binary); // Enable using LF rather than CRLF
  
  output << "P2" << std::endl; 
  output << "# File generated as " << file_name << std::endl;
  output << image_data.rows << "  " << image_data.cols << std::endl; 
  output << image_data.max_val << std::endl;

  int count{0};
  int max_count=image_data.cols; // Set the width to the cols
  for(int loopint: image_data.data){
      count++;
      output << loopint << "  ";
      if (count % max_count == 0) {
        output << std::endl;
      }
  }
  return true;
}


}  // namespace io_tools
}  // namespace igg