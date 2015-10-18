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
  EXPECT_EQ(s1.get_distance(0), -1);
  EXPECT_EQ(s1.get_distance(360), -1);
  EXPECT_EQ(s1.get_distance(1), 1);
  s1.set_distance(5,10);
  EXPECT_EQ(s1.get_distance(5), 10);
}

TEST_F(ScannerTest, rotate)
{
  s1.rotate(1);
  EXPECT_EQ(s1.get_distance(1), -1);
  EXPECT_EQ(s1.get_distance(2), 1);
  EXPECT_EQ(s1.get_distance(3), -1);
  s1.rotate(-3);
  EXPECT_EQ(s1.get_distance(359), 1);
  EXPECT_EQ(s1.get_distance(0), -1);
  EXPECT_EQ(s1.get_distance(1), -1);
}


TEST_F(ScannerTest, forward)
{
  EXPECT_EQ(s1.get_start(),0);
  EXPECT_EQ(s1.get_end(),360);
  s1.set_distance(90,100);
  s1.set_distance(45,100);
  s1.set_distance(-90,100);
  s1.set_distance(180,100);
  s1.set_distance(-45,100);
  s1.forward(50);
  EXPECT_EQ(s1.get_distance(90),50);
  EXPECT_EQ(s1.get_distance(-90),150);
}

TEST_F(ScannerTest, init)
{
  Scanner test1(1);
  EXPECT_EQ(test1.get_start(), 0);
  EXPECT_EQ(test1.get_end(), 360);
  Scanner test2(30);
  EXPECT_EQ(test2.get_start(), 0);
  EXPECT_EQ(test2.get_end(), 360);
  Scanner test3(50);
  EXPECT_EQ(test3.get_start(), 40);
  EXPECT_EQ(test3.get_end(), 340);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
