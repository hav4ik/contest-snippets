#include "common.hpp"
#include <gtest/gtest.h>


SNIPPET("gcd", "numbers.snippets", "GCD (simple)", "Greatest common divisor of integers")
inline TABSTOPWDEF(1,int) gcd(MIRRORWDEF(1,int) a, MIRRORWDEF(1,int) b) {
  while (b) { a %= b; swap (a, b); } return a;
}
TESTSNIPPET
TEST(GCDSimple, ComprehensiveCases) {
  ASSERT_EQ(gcd(7, 8), 1);
  ASSERT_EQ(gcd(100, 75), 25);
}
ENDSNIPPET


SNIPPET("gcd", "numbers.snippets", "GCD (extended)", "with x, y such that ax + by = gcd(a, b)")
TABSTOPWDEF(1,int) gcd (MIRRORWDEF(1,int) a, MIRRORWDEF(1,int) b, MIRRORWDEF(1,int) & x, MIRRORWDEF(1,int) & y) {
  if (a == 0) { x = 0; y = 1; return b; }
  MIRRORWDEF(1,int) x1, y1, d = gcd (b%a, a, x1, y1);
  x = y1 - (b / a) * x1; y = x1; return d;
}
TESTSNIPPET
TEST(GCDExtended, ComprehensiveCases) {
  int x, y;
  ASSERT_EQ(gcd(7, 8, x, y), 1);
  ASSERT_EQ(gcd(100, 75, x, y), 25);
}
ENDSNIPPET
