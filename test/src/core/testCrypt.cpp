#include "gtest/gtest.h"

namespace {
    class TestClass:public testing::Test{
    };
}

TEST_F(TestClass, Test_ReturnZeroMethod){
    GTEST_ASSERT_EQ(
        "123456", "123456"
    );
}
