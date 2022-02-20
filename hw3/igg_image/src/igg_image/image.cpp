#include<image.h>

namespace igg {
  
  Image::Image(const IoStrategy& io_strategy) : strategy{io_strategy} {};
  Image::Image(int rows, int cols, const IoStrategy& io_strategy) : rows_{rows}, cols_{cols}, strategy{io_strategy} { data_.reserve(rows*cols); };

  const int& Image::rows() const { return rows_; }
  const int& Image::cols() const { return cols_; }

  Image::Pixel& Image::at(int row, int col) { return data_[row * cols_ + col]; };   
  const Image::Pixel& Image::at(int row, int col) const { return data_[row * cols_ + col]; }; 


} // namespace igg