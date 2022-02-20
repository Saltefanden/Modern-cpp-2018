#pragma once

#include<vector>
#include<string>


namespace igg {

class Image {
 public:
  ///////////////////// Create the public interface here ///////////////////////
  Image();
  Image(int rows, int cols);

  const int& rows() const ;
  const int& cols() const ;
  const std::vector<int>& data() const ;

  int& at(int row, int col);
  const int& at(int row, int col) const; 

  bool FillFromPGM(const std::string& file_name);
  void WriteToPGM(const std::string& file_name) const;

  std::vector<float> ComputeHistogram(int bins) const;

  void DownScale(int scale); // Definitely not const!!
  void DownScale2(int scale); 
  void UpScale(int scale);


 private:
  int rows_ = 0;
  int cols_ = 0;
  int max_val_ = 255;
  std::vector<int> data_;
};

int ceil_div(int numerator, int denominator);

}  // namespace igg
