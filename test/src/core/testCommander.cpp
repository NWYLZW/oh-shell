#include <iostream>
using std::string;

#include "gtest/gtest.h"

#include "core/commander.h"

namespace {
    class TestClass:public testing::Test{
    };
}

TEST_F(TestClass, Test_Base_Surport) {
    auto cmd = string("ls");
    GTEST_ASSERT_EQ(
        string((
            *Commander::parser(cmd)
        )[0]->filename), string("ls")
    );

    auto commands = Commander::parser(string("ls -a -l"));
    GTEST_ASSERT_EQ(
        string((*commands)[0]->filename), string("ls")
    );
    GTEST_ASSERT_EQ((*commands)[0]->argv.size(), 3);
    GTEST_ASSERT_EQ(
        string((*commands)[0]->argv[0]), string("ls")
    );
    GTEST_ASSERT_EQ(
        string((*commands)[0]->argv[1]), string("-a")
    );
    GTEST_ASSERT_EQ(
        string((*commands)[0]->argv[2]), string("-l")
    );
}

TEST_F(TestClass, Test_Multi_Commands) {
    auto commands = Commander::parser(string("ls -a -l && echo 123"));
    GTEST_ASSERT_EQ(
        string((*commands)[0]->filename), string("ls")
    );
    GTEST_ASSERT_EQ(
        string((*commands)[1]->filename), string("echo")
    );

    commands = Commander::parser(string("ls -a -l; echo 123"));
    GTEST_ASSERT_EQ(
        string((*commands)[0]->filename), string("ls")
    );
    GTEST_ASSERT_EQ(
        string((*commands)[1]->filename), string("echo")
    );
}
