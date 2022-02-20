#include<gtest/gtest.h>
#include<image.h>
#include<io_tools.h>
#include<iostream>
#include<cstdio> 

TEST(Base, SmokeTest){
  EXPECT_EQ(1,1);
}

TEST(ImageClass, SmokeTest){
  EXPECT_NO_THROW(
    igg::Image image;
  );
}

TEST(ImageClass, GetRows){
  int rows{50};
  int cols{50};
  igg::Image image(rows, cols);
  EXPECT_EQ(rows, image.rows());
}

TEST(ImageClass, GetCols){
  int rows{50};
  int cols{50};
  igg::Image image(rows, cols);
  EXPECT_EQ(cols, image.cols());
}


TEST(ImageClass, DataReservationBuildup){
  // Tests how reservation affects capacity
  int rows{50};
  int cols{50};
  std::vector<int> myvec;
  myvec.reserve(rows*cols);
  EXPECT_EQ(rows*cols, myvec.capacity());
}

// Do a resize instead. Homework refers to the operation as resize.
TEST(ImageClass, DataResizeBuildup){
  // Tests how resizing affects capacity
  int rows{50};
  int cols{50};
  std::vector<int> myvec;
  myvec.resize(rows*cols);
  EXPECT_EQ(rows*cols, myvec.capacity());
}

TEST(ImageClass, DataResizing){
  // Tests that resizing works in image class. 
  int rows{50};
  int cols{50};
  igg::Image image(rows, cols);

  std::vector<int> myvec;
  myvec.resize(rows*cols);

  EXPECT_EQ(myvec.capacity(), image.data().capacity());
}

//######### REMOVED - SHOULD NOT APPLY ####################
// TEST(ImageClass, ManualSetter){
//   // Set the data manually
//   int rows{40};
//   int cols{40};
//   igg::Image image(rows, cols);
//   int setval{4};

//   EXPECT_NO_THROW(
//     image.data()[10 * image.cols() + 10] = setval;
//   );
// }


TEST(ImageClass, Getter){
  // Get the value of the zero initialized vector
  int rows{40};
  int cols{40};
  igg::Image image(rows, cols);
  int val = image.at(2,2);

  EXPECT_EQ(0, val);
  // EXPECT_NO_THROW(val = 4;);
  // EXPECT_EQ(val, image.at(2,2));
}

TEST(ImageClass, Setter){
  // Set the value at an index. Check that this value is set correctly by getting it afterwards.
  int rows{40};
  int cols{40};
  igg::Image image(rows, cols);
  int setval{7};
  image.at(2,2) = setval;

  EXPECT_EQ(setval, image.at(2,2));
}

TEST(ExternalLibrary, SmokeTest){
  std::vector<int> my_vec = {1,2,3};
  igg::io_tools::ImageData my_imdat{1,2,3,my_vec};
}

TEST(ExternalLibrary, FillFromPGMTrue){
  igg::Image test_image;
  EXPECT_TRUE(test_image.FillFromPGM("data/lena.ascii.pgm"));
}

TEST(ExternalLibrary, FillFromPGM){
  igg::Image test_image;
  test_image.FillFromPGM("../data/lena.ascii.pgm"); // Test working directory is same as binary directory (Line 40 in tests/CMakeLists.txt)
  int this_image_cols = test_image.cols();
  int max_col_index = this_image_cols - 1;
  EXPECT_EQ(162, test_image.at(0,0));
  EXPECT_EQ(161, test_image.at(0,3));
  EXPECT_EQ(128, test_image.at(0,max_col_index));
  EXPECT_EQ(162, test_image.at(1,0));
  EXPECT_EQ(161, test_image.at(1,3));
  EXPECT_EQ(107, test_image.at(max_col_index,max_col_index));
}

TEST(ExternalLibrary, WriteToPGM){
  std::string file_name = "../data/test_written.pgm";
  igg::Image test_image(2,2);
  test_image.at(0,0) = 1;
  test_image.at(1,0) = 2;
  test_image.at(0,1) = 3;
  test_image.at(1,1) = 4;
  test_image.WriteToPGM(file_name);

  // Test: See if file_name is readable.
  std::ifstream dummy_to_see_if_readable(file_name);
  EXPECT_TRUE(dummy_to_see_if_readable.good());

  // Teardown - uncomment to see result
  dummy_to_see_if_readable.close();
  EXPECT_NE(-1, std::remove(file_name.c_str()));
}

TEST(ExternalLibrary, WriteAndRead){
  std::string file_name = "../data/test_written.pgm";
  igg::Image test_image(2,2);
  test_image.at(0,0) = 1;
  test_image.at(1,0) = 2;
  test_image.at(0,1) = 3;
  test_image.at(1,1) = 4;
  test_image.WriteToPGM(file_name);

  // Test: See if file is parsable as PGM file.
  igg::Image second_test_image;
  second_test_image.FillFromPGM(file_name);
  EXPECT_EQ(second_test_image.at(0,0), test_image.at(0,0));
  EXPECT_EQ(second_test_image.at(1,0), test_image.at(1,0));
  EXPECT_EQ(second_test_image.at(0,1), test_image.at(0,1));
  EXPECT_EQ(second_test_image.at(1,1), test_image.at(1,1));

  // Teardown - uncomment to see result
  EXPECT_NE(-1, std::remove(file_name.c_str()));  
}


TEST(ImageClass, WriteAndRead){
  igg::Image test_image;
  test_image.FillFromPGM("../data/lena.ascii.pgm"); 
  test_image.WriteToPGM("../data/Lena.pgm");
}


TEST(ImageClass, Histogram){
  igg::Image test_image(2,2);
  test_image.at(0,0) = 256/10 * 1;
  test_image.at(1,0) = 256/10 * 3;
  test_image.at(0,1) = 256/10 * 7;
  test_image.at(1,1) = 255;
  std::vector<float> my_histogram = test_image.ComputeHistogram(10);
  std::vector<float> expected_histogram = {0.25f, 0.0f, 0.25f, 0.0f, 0.0f, 0.0f, 0.25f, 0.0f, 0.0f, 0.25f};
  EXPECT_EQ(expected_histogram, my_histogram);
}


TEST(ImageClass, Histogramlol){
  igg::Image test_image;
  test_image.FillFromPGM("../data/lena.ascii.pgm"); 
  std::vector<float> my_histogram = test_image.ComputeHistogram(200);

  std::ofstream output("../data/LenaHistogram.txt");
  for (float bin: my_histogram){
    output << bin << " ";
  }
}



TEST(AuxFuncs, Divisions){
  EXPECT_EQ(3, igg::ceil_div(5,2));
  EXPECT_EQ(3, igg::ceil_div(6,2));
  EXPECT_EQ(2, igg::ceil_div(5,3));
  EXPECT_EQ(2, igg::ceil_div(6,3));
}


TEST(ImageClass, DownScale){
  igg::Image test_image;
  test_image.FillFromPGM("../data/lena.ascii.pgm"); 
  test_image.DownScale(2);

  test_image.WriteToPGM("../data/Downscaled_Lena.pgm");
}

TEST(ImageClass, DownScale_second){
  igg::Image test_image;
  test_image.FillFromPGM("../data/lena.ascii.pgm"); 
  test_image.DownScale2(2);

  test_image.WriteToPGM("../data/Downscaled2_Lena.pgm");
}


TEST(ImageClass, DownScaleByOddNumber){
  igg::Image test_image;
  test_image.FillFromPGM("../data/lena.ascii.pgm"); 
  test_image.DownScale(3);

  test_image.WriteToPGM("../data/Downscaled_Lena_3.pgm");
}

TEST(ImageClass, DownScaleByALot){
  igg::Image test_image;
  test_image.FillFromPGM("../data/lena.ascii.pgm"); 
  test_image.DownScale(13);

  test_image.WriteToPGM("../data/Downscaled_Lena_13.pgm");
}


TEST(ImageClass, UpScale){
  igg::Image test_image;
  test_image.FillFromPGM("../data/lena.ascii.pgm"); 
  test_image.UpScale(2);

  test_image.WriteToPGM("../data/Upscaled_Lena.pgm");
}

TEST(ImageClass, UpScaleOddNumber){
  igg::Image test_image;
  test_image.FillFromPGM("../data/lena.ascii.pgm"); 
  test_image.UpScale(3);

  test_image.WriteToPGM("../data/Upscaled_Lena3.pgm");
}



