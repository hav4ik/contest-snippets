#pragma once
#include "../macros.hpp"
#include <gtest/gtest.h>


MACROSNIPPET("head", "skeleton.snippets", "Common", "commonly used #includes and convenient macros")
/// basic i/o includes
#include <iostream>
#include <sstream>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <complex>

/// data structures and algorithms
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <bitset>

/// i never use that in serious projects
using namespace std;

/// defines for retards
#define forn(i, n) for (auto i = 0; i < (n); ++i)
#define for1(i, n) for (auto i = 1; i <= (n); ++i)
#define forab(i, a, b) for (auto i = (a); i <= (b); ++i)
#define all(a) (a).begin(), (a).end();
#define rall(a) (a).rbegin(), (a).rend();
#define pb(a) push_back(a)
#define ppb(a) pop_back(a)
#define fir first
#define sec second
typedef unsigned long long int ulli;

TABSTOP(0)
ENDMACROSNIPPET



INLINESNIPPET("body", "skeleton.snippets", "CodeJam", "Google Code Jam style body")
/// Define some global variables here
TABSTOP(1)

void solve(int tcase)
{
  /// Write solution here
  TABSTOP(0)

  /// Write answer
  cout << "Case #" << tcase << ": " << endl;
}

int main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  int testcases;
  cin >> testcases;
  for1(t, testcases)
      solve(t);
  return 0;
}
ENDINLINESNIPPET


INLINESNIPPET("body", "skeleton.snippets", "Codeforces", "Codeforces style body")
/// Define global variables here
TABSTOP(1)

int main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  /// Write your solution here
  TABSTOP(0)

  return 0;
}
ENDINLINESNIPPET
