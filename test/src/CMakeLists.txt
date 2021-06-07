add_executable(
    test_cryptor ./core/testCrypt.cpp
)

target_link_libraries(
    test_cryptor gtest gtest_main
)
