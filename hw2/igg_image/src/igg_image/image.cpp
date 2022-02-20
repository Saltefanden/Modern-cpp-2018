#include<image.h>
#include<io_tools.h>
#include<vector>
#include<string>

namespace igg{


Image::Image(int rows, int cols): rows_{rows}, cols_{cols} {
  data_.resize(rows*cols);
}


Image::Image(){};


const int& Image::rows() const { // Strictly only getter functions for rows and cols
  return rows_;
}


const int& Image::cols() const { // Strictly only getter functions for rows and cols
  return cols_;
}


const std::vector<int>& Image::data() const { // Strictly only getter function for data
  return data_;
}


// Getter and setter for non const objects
int& Image::at(int row, int col) {
  return data_[row * cols_ + col]; // row major order
}


// Getter for const objects
const int& Image::at(int row, int col) const {
  return data_[row * cols_ + col]; 
}


bool Image::FillFromPGM(const std::string& file_name) {
  io_tools::ImageData read_ImageData = io_tools::ReadFromPgm(file_name);
  rows_ = read_ImageData.rows;
  cols_ = read_ImageData.cols;
  max_val_ = read_ImageData.max_val;
  data_ = read_ImageData.data;
  return true;
}


void Image::WriteToPGM(const std::string& file_name) const {
  io_tools::ImageData image_data{
    rows_,
    cols_,
    max_val_,
    data_
  };
  io_tools::WriteToPgm(image_data, file_name);
}


std::vector<float> Image::ComputeHistogram(int bins) const {
  std::vector<float> Histogram;
  Histogram.resize(bins); // Defaults all values to 0 unless otherwise specified >>> Histogram.resize(bins, default_val)

  int total_number_of_pixels = rows_ * cols_;
  
  // How many pixel values are possible
  int total_pixel_range = max_val_ + 1; // Since pixel value of 0 is allowed, the range from e.g. 0 to 255 spans 256 integer values.

  // How many pixel values should each bin cover
  float bin_width = (float)total_pixel_range / (float)bins;

  // How much does each pixel contribute in the histogram
  float pixel_contribution = 1.0f/total_number_of_pixels;
  
  for (int pixel_value: data_) {
    // Which bin does the pixel value correspond to:
    // Floor divide the value with the bin_width to get the correct bin index in the Histogram vector
    int bin = pixel_value / bin_width; 

    // Add the contribution of this pixel to its computed bin
    Histogram[bin] += pixel_contribution; 
  }

  return Histogram;
}


int ceil_div(int numerator, int denominator){
  return (numerator + denominator - 1) / denominator;
}


void Image::DownScale(int scale) {
  // new row and column size after rescaling
  int new_rows = ceil_div(rows_, scale); 
  int new_cols = ceil_div(cols_, scale);

  std::vector<int> new_data;
  new_data.reserve(new_rows * new_cols);

  // Loop over every pixel index, i, in data_ vector
  for (std::size_t i = 0; i < data_.size(); ++i) {
    int current_row = i / cols_;
    int current_col = i % cols_;
    // Take every scale'th pixel by ensuring that both the current row and column mod scale is zero.
    if ( (current_row % scale == 0) && (current_col % scale == 0) ) {
      new_data.emplace_back(data_[i]);
    }
  }
  rows_ = new_rows;
  cols_ = new_cols;
  data_ = new_data;
}


void Image::DownScale2(int scale) {
  // This implementation is more logical? Faster
  // new row and column size after rescaling
  int new_rows = ceil_div(rows_, scale); 
  int new_cols = ceil_div(cols_, scale);

  std::vector<int> new_data;
  new_data.reserve(new_rows * new_cols);

  for (int row=0; row < rows_; ++row) {
    if ( row % scale == 0 ) {
      for (int col=0; col < cols_; ++col){
        if (col % scale == 0) {
          new_data.emplace_back(data_[row * cols_ + col]);
        }
      }
    }
  }

  rows_ = new_rows;
  cols_ = new_cols;
  data_ = new_data;
}


void Image::UpScale(int scale) {
  // new row and column size after rescaling
  int new_rows = rows_ * scale; 
  int new_cols = cols_ * scale;

  std::vector<int> new_data;
  new_data.reserve(new_rows * new_cols);

  for ( int row=0; row < rows_; ++row ) {
    // Repeat every row <scale> times
    for ( int i=0; i < scale; ++i ) { 
      for ( int col=0; col < cols_; ++col ){
        // Repeat every col <scale> times
        for ( int j=0; j < scale; ++j ) {
          new_data.emplace_back(data_[row * cols_ + col]);
        }
      }
    }
  }

  rows_ = new_rows;
  cols_ = new_cols;
  data_ = new_data;

}



} // namespace igg
