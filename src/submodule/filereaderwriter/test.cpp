#include <gtest/gtest.h>

TEST(Tests, CameraTest){
    bool isSuccess = false;
    EXPECT_EQ(true, isSuccess);
    std::cout<<"HellO" ;
}

TEST(Tests, CameraTest2){
    bool isSuccess = true;
    EXPECT_EQ(true, isSuccess);
    //ASSERT_TRUE(true, isSuccess)       //if dont Pass code will not continue testing
}


