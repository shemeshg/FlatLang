# Todo and draft

test logical gates
```
#include <stdexcept>
#include <iostream>

void test_and() {
    if ((true && true) != true) throw std::runtime_error("AND failed: true && true");
    if ((true && false) != false) throw std::runtime_error("AND failed: true && false");
    if ((false && true) != false) throw std::runtime_error("AND failed: false && true");
    if ((false && false) != false) throw std::runtime_error("AND failed: false && false");
}

void test_or() {
    if ((true || true) != true) throw std::runtime_error("OR failed: true || true");
    if ((true || false) != true) throw std::runtime_error("OR failed: true || false");
    if ((false || true) != true) throw std::runtime_error("OR failed: false || true");
    if ((false || false) != false) throw std::runtime_error("OR failed: false || false");
}

void test_not() {
    if ((!true) != false) throw std::runtime_error("NOT failed: !true");
    if ((!false) != true) throw std::runtime_error("NOT failed: !false");
}

void test_nand() {
    if (!(true && true) != false) throw std::runtime_error("NAND failed: !(true && true)");
    if (!(true && false) != true) throw std::runtime_error("NAND failed: !(true && false)");
    if (!(false && true) != true) throw std::runtime_error("NAND failed: !(false && true)");
    if (!(false && false) != true) throw std::runtime_error("NAND failed: !(false && false)");
}

void test_xor() {
    if ((true ^ true) != false) throw std::runtime_error("XOR failed: true ^ true");
    if ((true ^ false) != true) throw std::runtime_error("XOR failed: true ^ false");
    if ((false ^ true) != true) throw std::runtime_error("XOR failed: false ^ true");
    if ((false ^ false) != false) throw std::runtime_error("XOR failed: false ^ false");
}

int main() {
    try {
        test_and();
        test_or();
        test_not();
        test_nand();
        test_xor();
        std::cout << "All logic tests passed.\n";
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << '\n';
        return 1;
    }
    return 0;
}

```

google test
```
TEST(LogicGateTest, AND) {
    EXPECT_TRUE(logic_and(true, true));
    EXPECT_FALSE(logic_and(true, false));
    EXPECT_FALSE(logic_and(false, true));
    EXPECT_FALSE(logic_and(false, false));
}

TEST(LogicGateTest, OR) {
    EXPECT_TRUE(logic_or(true, true));
    EXPECT_TRUE(logic_or(true, false));
    EXPECT_TRUE(logic_or(false, true));
    EXPECT_FALSE(logic_or(false, false));
}

TEST(LogicGateTest, NOT) {
    EXPECT_FALSE(logic_not(true));
    EXPECT_TRUE(logic_not(false));
}

TEST(LogicGateTest, NAND) {
    EXPECT_FALSE(logic_nand(true, true));
    EXPECT_TRUE(logic_nand(true, false));
    EXPECT_TRUE(logic_nand(false, true));
    EXPECT_TRUE(logic_nand(false, false));
}

TEST(LogicGateTest, XOR) {
    EXPECT_FALSE(logic_xor(true, true));
    EXPECT_TRUE(logic_xor(true, false));
    EXPECT_TRUE(logic_xor(false, true));
    EXPECT_FALSE(logic_xor(false, false));
}

TEST(LogicGateTest, XNOR) {
    EXPECT_TRUE(logic_xnor(true, true));
    EXPECT_FALSE(logic_xnor(true, false));
    EXPECT_FALSE(logic_xnor(false, true));
    EXPECT_TRUE(logic_xnor(false, false));
}

```

```
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

```
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)
```

```
enable_testing()

add_executable(logic_tests logic_tests.cpp)
target_link_libraries(logic_tests gtest_main)

include(GoogleTest)
gtest_discover_tests(logic_tests)
```

```
ctest --verbose

```