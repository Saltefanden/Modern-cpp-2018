#include<image.h>

namespace igg {
  
  Image::Image(const IoStrategy& io_strategy) : strategy{io_strategy} {};
  Image::Image(int rows, int cols, const IoStrategy& io_strategy) : rows_{rows}, cols_{cols}, strategy{io_strategy} { data_.reserve(rows*cols); };

  const int& Image::rows() const { return rows_; }
  const int& Image::cols() const { return cols_; }

  Image::Pixel& Image::at(int row, int col) { return data_[row * cols_ + col]; };   
  const Image::Pixel& Image::at(int row, int col) const { return data_[row * cols_ + col]; }; 

  int ceil_div(int numerator, int denominator){
    return (numerator + denominator - 1) / denominator;
  }

  void Image::DownScale(int scale){
    std::vector<Pixel> new_data;
    int new_rows = ceil_div(rows_, scale); 
    int new_cols = ceil_div(cols_, scale); 
    new_data.reserve(new_rows * new_cols);
    for (int row=0; row < rows_; ++row ){
      if (row % scale == 0){
        for (int col=0; col < cols_; ++col){
          if (col % scale == 0){
            // If the rows and cols are "allowed" then 
            new_data.push_back(Image::at(row, col));
          }
        }
      }
    }
    rows_ = new_rows;
    cols_ = new_cols;
    data_ = new_data;
  }

  void Image::UpScale(int scale){
    std::vector<Pixel> new_data;
    int new_rows = rows_ * scale;
    int new_cols = cols_ * scale;
    new_data.reserve(new_rows * new_cols);
    for (int row=0; row < rows_; ++row){
      for (int repeat_row=0; repeat_row < scale; ++repeat_row){
        for (int col=0; col < cols_; ++col){
          for (int repeat_col=0; repeat_col < scale; ++repeat_col){
            new_data.push_back(Image::at(row, col));
          }
        }  
      }
    }
    rows_ = new_rows;
    cols_ = new_cols;
    data_ = new_data;
  }

  bool Image::ReadFromDisk(const std::string& file_name){
    // Read file_name into imagedata
    ImageData imagedata = strategy.Read(file_name);
    int image_size = imagedata.rows * imagedata.cols;

    // Convert to Image class data
    std::vector<int> red_vec = imagedata.data[0]; 
    std::vector<int> green_vec = imagedata.data[1]; 
    std::vector<int> blue_vec = imagedata.data[2]; 

    std::vector<Pixel> file_data;
    file_data.reserve(image_size);

    for (int i=0; i < image_size; ++i){
      Pixel current_pixel = {red_vec[i], green_vec[i], blue_vec[i]};
      file_data.push_back(current_pixel);
    }
    
    rows_ = imagedata.rows;
    cols_ = imagedata.cols;
    data_ = file_data;

    return true;
  }

  void Image::WriteToDisk(const std::string& file_name){

  }

} // namespace igg