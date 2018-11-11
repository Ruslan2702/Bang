//
// Created by ruslan on 10.11.18.
//

#include <gtest/gtest.h>
#include <iostream>


class MyTestCase : public ::testing::Test {
public:
    void SetUp() {
        count = 0;
    }

    void TearDown() {

    }

    int count;
};

TEST_F(MyTestCase, test1) {
    ASSERT_EQ(count, 0);
}

TEST_F(MyTestCase, test2) {
    ASSERT_FALSE(count);
}


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}