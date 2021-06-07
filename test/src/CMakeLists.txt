add_executable(
    test_commander
    core/testCommander.cpp
    ../../src/core/commander.cpp
)

target_link_libraries(
    test_commander gtest gtest_main
)
