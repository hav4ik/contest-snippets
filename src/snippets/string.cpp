#include "common.hpp"

#include <string>
#include <vector>
using namespace std;



SNIPPET("prefix", "strings.snippets", "Prefix Function (STL)", "STL version of prefix function")
void prefix_function(TABSTOPWDEF(1,string&) s, TABSTOPWDEF(2,vector<int>&) p) {
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



SNIPPET("zfunc", "strings.snippets", "Z-function (STL)", "Calculates Z-function in O(n)")
void z_function(TABSTOPWDEF(1,string&) s, TABSTOPWDEF(2,vector<int>&) z) {
    int n = (int) s.length(); z.resize(n);
    for (int i=1, l=0, r=0; i<n; ++i) {
        if (i <= r) z[i] = min (r-i+1, z[i-l]);
        while (i+z[i] < n && s[z[i]] == s[i+z[i]]) ++z[i];
        if (i+z[i]-1 > r) l = i,  r = i+z[i]-1;
    }
}
TESTSNIPPET
TEST(ZFunctionSTL, SimpleCases) {
    string s1 = "aaaaa", s2 = "aaabaab", s3 = "abacaba";
    const int a1[] = {0,4,3,2,1}, a2[] = {0,2,1,0,2,1,0}, a3[] = {0,0,1,0,3,0,1};
    vector<int> z1, z2, z3;
    z_function(s1, z1); z_function(s2, z2); z_function(s3, z3);
    for (int i = 0; i < s1.length(); i++) ASSERT_EQ(a1[i], z1[i]);
    for (int i = 0; i < s2.length(); i++) ASSERT_EQ(a2[i], z2[i]);
    for (int i = 0; i < s3.length(); i++) ASSERT_EQ(a3[i], z3[i]);
}
ENDSNIPPET



