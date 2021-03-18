#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include <iostream>
#include <string>

extern int num_tests_passed;
extern int num_tests_failed;

template <typename T>
bool test(T actual, T expected, std::string test_name, int indent) {
    std::string space(indent, ' ');
    bool passed = actual == expected;
    std::cout << space << test_name << ": " << (passed ? "PASSED" : "FAILED") << std::endl;
    if (!passed) {
        std::cout << "  " << space << "ACTUAL: " << actual << std::endl;
        std::cout << "  " << space << "EXPECTED: " << expected << std::endl;
        num_tests_failed++;
    } else
        num_tests_passed++;

    return passed;
}
void print_test_summary();

#endif  // TEST_HELPERS_H