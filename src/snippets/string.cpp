#include "common.hpp"
#include <gtest/gtest.h>

#include <string>
#include <vector>
using namespace std;


SNIPPET("prefix", "strings.snippets", "Prefix Function (STL)", "STL version of prefix function")
void prefix_function(TABSTOP(1,string&) s, TABSTOP(2,vector<int>&) p) {
    p.resize(s.length(), 0);
    for (size_t i = 1; i < s.length(); ++i) {
        size_t j = p[i - 1];
        while (j > 0 && s[i] != s[j]) j = p[j - 1];
        if (s[i] == s[j]) ++j; p[i] = j;
    }
}
TESTSNIPPET
TEST(PrefixFunctionSTL, SimpleCases) {
    string s = "aabaaab";
    const int answer[] = {0, 1, 0, 1, 2, 2, 3};
    vector<int> p;
    prefix_function(s, p);
    for (size_t i = 0; i < s.length(); ++i)
        ASSERT_EQ(answer[i], p[i]);
}
TEST(PrefixFunctionSTL, EdgeCases) {
    string s = "";
    vector<int> p;
    prefix_function(s, p);
    ASSERT_EQ(p.size(), 0);
}
ENDSNIPPET



