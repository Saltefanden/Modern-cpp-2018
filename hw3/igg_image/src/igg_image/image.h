// Copyright Igor Bogoslavskyi, year 2018.
// In case of any problems with the code please contact me.
// Email: igor.bogoslavskyi@uni-bonn.de.

#pragma once

#include<vector>
#include<strategy.h>


namespace igg {

class Image {
 public:
  /// A struct within class Image that defines a pixel.
  struct Pixel {
    int red;
    int green;
    int blue;
  };

  // TODO: fill public interface.
  Image(const IoStrategy& io_strategy); 
  Image(int rows, int cols, const IoStrategy& io_strategy); 

  const int& rows() const; 
  const int& cols() const;

  Pixel& at(int row, int col);              // Non const getter setter
  const Pixel& at(int row, int col) const;  // const only getter

  void DownScale(int scale);
  void UpScale(int scale);

  bool ReadFromDisk(const std::string& file_name);
  void WriteToDisk(const std::string& file_name);

  const std::vector<Pixel>& GetData() const;

 private:

  // TODO: add missing private members when needed.

  int rows_ = 0;
  int cols_ = 0;
  int max_val_ = 255;
  std::vector<Pixel> data_;
  const IoStrategy& strategy; 

};

}  // namespace igg
