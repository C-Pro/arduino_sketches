#include "gtest/gtest.h"
#include "scanner.h"

class ScannerTest : public ::testing::Test
{
protected:
  virtual void SetUp()
  {
    s1.set_distance(1,1);
  }

  Scanner s1;
};

TEST_F(ScannerTest, normalize)
{
  EXPECT_EQ(s1.normalize(0),0);
  EXPECT_EQ(s1.normalize(90),90);
  EXPECT_EQ(s1.normalize(360),0);
  EXPECT_EQ(s1.normalize(361),1);
  EXPECT_EQ(s1.normalize(-90),270);
  EXPECT_EQ(s1.normalize(-360),0);
}

TEST_F(ScannerTest, get_distance) {
  EXPECT_EQ(-1, s1.get_distance(0));
  EXPECT_EQ(-1, s1.get_distance(360));
  EXPECT_EQ(1, s1.get_distance(1));
  s1.set_distance(5,10);
  EXPECT_EQ(10,s1.get_distance(5));
  s1.rotate(-1);
}

TEST_F(ScannerTest, rotate)
{
  s1.rotate(1);
  EXPECT_EQ(-1, s1.get_distance(1));
  EXPECT_EQ(1, s1.get_distance(2));
  EXPECT_EQ(-1, s1.get_distance(3));
  s1.rotate(-3);
  EXPECT_EQ(1, s1.get_distance(359));
  EXPECT_EQ(-1, s1.get_distance(0));
  EXPECT_EQ(-1, s1.get_distance(1));
}


TEST_F(ScannerTest, forward)
{
  s1.set_distance(90,100);
  s1.set_distance(45,100);
  s1.set_distance(-90,100);
  s1.set_distance(180,100);
  s1.set_distance(-45,100);
  s1.forward(50);
  EXPECT_EQ(s1.get_distance(90),50);
  EXPECT_EQ(s1.get_distance(-90),150);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
