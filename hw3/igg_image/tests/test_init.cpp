#include<gtest/gtest.h>
#include<image.h>
#include<dummy_strategy.h>
#include<string>


TEST(BaseTest, SmokeTest) {
  EXPECT_TRUE(true);
}


TEST(ImageLibrary, Initializer) {
  igg::DummyIoStrategy test_strategy;
  igg::Image image(test_strategy);
  igg::Image image2(3, 3, test_strategy);
}


TEST(ImageLibrary, InitializeAndGetters) {
  igg::DummyIoStrategy test_strategy;
  int rows{7};
  int cols{85};
  igg::Image image(rows, cols, test_strategy);
  EXPECT_EQ(rows, image.rows());
  EXPECT_EQ(cols, image.cols());
}


TEST(ImageLibrary, SetGetPixelValues) {
  igg::DummyIoStrategy test_strategy;
  int rows{3};
  int cols{3};

  igg::Image image(rows, cols, test_strategy);
  
  image.at(0,0) = igg::Image::Pixel{255, 0, 0}; // red
  image.at(0,1) = {0, 255, 0}; // green
  image.at(0,2) = {0, 0, 255}; // blue

  igg::Image::Pixel RedPixel{255, 0, 0};
  EXPECT_EQ(RedPixel.red, image.at(0,0).red);
  EXPECT_EQ(RedPixel.green, image.at(0,0).green);
  EXPECT_EQ(RedPixel.blue, image.at(0,0).blue);
  EXPECT_EQ(255, image.at(0,1).green);
  EXPECT_EQ(255, image.at(0,2).blue);
}


TEST(ImageLibrary, DownScale){
  igg::DummyIoStrategy test_strategy;
  int rows{3};
  int cols{3};

  igg::Image image(rows, cols, test_strategy);

  image.at(0,0) = {0, 255, 0};

  image.DownScale(2);

  EXPECT_EQ(image.rows(), 2);
  EXPECT_EQ(image.cols(), 2);

}

TEST(ImageLibrary, UpScale){
  igg::DummyIoStrategy test_strategy;
  int rows{3};
  int cols{3};

  igg::Image image(rows, cols, test_strategy);

  image.at(0,0) = {0, 255, 0};

  image.UpScale(2);

  EXPECT_EQ(image.rows(), 6);
  EXPECT_EQ(image.cols(), 6);
  EXPECT_EQ(image.at(0,0).green, image.at(1,1).green);
  EXPECT_EQ(image.at(0,0).red, image.at(1,1).red);
  EXPECT_EQ(image.at(0,0).blue, image.at(1,1).blue);
  EXPECT_NE(image.at(0,0).green, image.at(2,2).green);
}


TEST(ImageLibrary, DummyStrategyRead){
  igg::DummyIoStrategy test_strategy;
  int rows{3};
  int cols{3};
  
  igg::Image image(rows, cols, test_strategy);

  EXPECT_TRUE(image.ReadFromDisk("Lol"));

  EXPECT_EQ(image.rows(), 0);
}

TEST(ImageLibrary, DummyStrategyWrite){
  igg::DummyIoStrategy test_strategy;
  int rows{3};
  int cols{3};
  
  igg::Image image(rows, cols, test_strategy);

  image.WriteToDisk("Lol");
  

}

