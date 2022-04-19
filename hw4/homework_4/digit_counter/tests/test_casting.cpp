#include<gtest/gtest.h>

TEST(Smoketest, True){
  EXPECT_EQ(true, true);
}


TEST(RegularCasting, CastIntToChar){
  int x{53};
  char& y = reinterpret_cast<char&>(x);
  EXPECT_EQ( y, '5' );
}