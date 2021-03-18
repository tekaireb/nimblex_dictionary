#include "test_helpers.h"

using namespace std;

int num_tests_passed;
int num_tests_failed;

void print_test_summary() {
    cout << endl
         << "SUMMARY:" << endl
         << "  Passed " << num_tests_passed << '/' << (num_tests_passed + num_tests_failed) << " tests" << endl;
}