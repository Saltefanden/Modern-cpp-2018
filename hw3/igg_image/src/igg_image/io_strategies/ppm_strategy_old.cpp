#include<string>
#include<vector>
#include<strategy.h>
#include<ppm_strategy.h>
#include<sstream>

namespace igg {

  void SetToDimensions(std::stringstream& my_sstream, ImageData& image_data){
    my_sstream >> image_data.rows >> image_data.cols;
    int vector_size{ image_data.rows * image_data.cols };
    image_data.data.reserve(3*vector_size); // Three channels? Will this be good enough?
  }

  void SetToMaxVal(std::stringstream& my_sstream, ImageData& image_data){
    my_sstream >> image_data.max_val;
  }

  void SetToData(std::stringstream& my_sstream, ImageData& image_data) {
    int red_val;
    int green_val;
    int blue_val;

    while (my_sstream >> red_val >> green_val >> blue_val) {
      std::vector<int> pixel{red_val, green_val, blue_val};
      image_data.data.push_back(pixel);
    }
  }

  bool PpmIoStrategy::Write(const std::string& file_name, const ImageData& data) const {
    std::ofstream output(file_name, std::ios::binary); // Enable using LF rather than CRLF
    output << "P3" << std::endl; 
    output << "# File generated as " << file_name << std::endl;
    output << data.rows << "  " << data.cols << std::endl; 
    output << data.max_val << std::endl;

    int count{0};
    int max_count=data.cols; // Set the width to the cols
    for(int i=0; i < (data.rows*data.cols); ++i){
      count++;
      for (int color_no=0; color_no<3; ++color_no){
        output << data.data[color_no][i] << "  ";
      }
      if (count % max_count == 0) {
        output << std::endl;
      } 
    }
    return true;
  }
  
  ImageData PpmIoStrategy::Read(const std::string& file_name) const {
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


} // namespace igg.




