#include "common.hpp"
#include <gtest/gtest.h>



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
    if (i+z[i]-1 > r) l = i, r = i+z[i]-1;
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



SNIPPET("trie", "strings.snippets", "Trie (prefix)", "Simple prefix tree")
class Trie {
public:
  // TODO: set the [SIZE] of your alphabet (number of characters)
  static const int abc_size = TABSTOPWDEF(1,26);

  struct Node {
    int n[abc_size], p;

    // TODO: set the [TYPE] of your alphabet (type of chars)
    TABSTOPWDEF(2,char) c;

    int wend;
    Node(MIRRORWDEF(2,char) i): p(-1), wend(0), c(i) {
      for (auto it = n; it != n + abc_size; ++it)
        *it = -1;
    }

    int& operator [](MIRRORWDEF(2,char) i) {
      // TODO: define how you will convert a char to its id (starting from 0)
      return n[TABSTOPWDEF(3,i - 'a')];
    }
  };

  vector<Node> t;
  Node& operator [](int i) { return t[i]; }

  Trie(int capacity=0) {
    if (capacity > 0) t.reserve(capacity);
    reset();
  }

  void reset() {
    t.clear();             // cpp standard guarantees not to change the capacity.
    t.push_back(Node(0));  // (see https://stackoverflow.com/questions/18467624)
  }

  // TODO: strings for the trie (hint: any STL iterable container)
  void add(TABSTOPWDEF(4,const string&) s) {
    int idx = 0, nxt;
    for (auto c = s.begin(); c != s.end(); ++c) {
      nxt = t[idx][*c];
      if (nxt == -1) {
        t.push_back(Node(*c));
        t[idx][*c] = t.size() - 1;
        t.back().p = idx;
        idx = t.size() - 1;
      }
      else
        idx = nxt;
    }
    t[idx].wend++;
  }

  int find(MIRRORWDEF(4,const string&) s) {
    int idx = 0, nxt;
    for (auto c = s.begin(); c != s.end(); ++c) {
      nxt = t[idx][*c];
      if (nxt == -1)
        return -1;
      else
        idx = nxt;
    }
    return idx;
  }

  // WARNING: does not clean the memory!!! just removes the links!!!
  void remove(MIRRORWDEF(4, const string&) s) {
    int idx = find(s), prv;
    if (idx != -1) {
      if (t[idx].wend <= 0) return;
      t[idx].wend--;
      if (t[idx].wend == 0) {
        for (auto it = t[idx].n; it != t[idx].n + abc_size; ++it)
          if (*it != -1) return;
        while (t[idx].wend == 0) {
          prv = t[idx].p;
          if (prv == -1) return;
          t[prv][t[idx].c] = -1;
          idx = prv;
        }
      }
    }
  }

  inline int count(MIRRORWDEF(4,const string&) s) {
    return t[find(s)].wend;
  }
};

TABSTOP(5)
TESTSNIPPET
TEST(SimpleTrie, ComprehensiveTest) {
  Trie trie;          ASSERT_EQ(trie.t.size(), 1);
  trie.add("");       ASSERT_EQ(trie[0].wend, 1);
  trie.add("a");      ASSERT_EQ(trie[1].p, 0);
  trie.add("aa");     ASSERT_EQ(trie[2].wend, 1);
  trie.add("ab");     ASSERT_EQ(trie[3].wend, 1);
  trie.add("aab");    ASSERT_EQ(trie[4].wend, 1);
  trie.add("ghjh");   ASSERT_EQ(trie[8].wend, 1);
  trie.remove("aa");  ASSERT_EQ(trie[2].wend, 0);
  trie.remove("");    ASSERT_EQ(trie[0].wend, 0);
}
ENDSNIPPET
