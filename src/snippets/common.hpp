#pragma once
#include "../macros.hpp"
#include <gtest/gtest.h>


MACROSNIPPET("head", "skeleton.snippets", "Common", "commonly used #includes and convenient macros")
/**
 *    USING VIM SNIPPETS FOR CODING COMPETITIONS
 *    https://github.com/hav4ik/contest-snippets
 *
 *    author:   hav4ik (chankhavu@gmail.com)
 *    created:  `date +%d.%m.%y`
**/

#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for (auto i = 0; i < (n); ++i)
#define forr(i, n) for (auto i = (n); i-- > 0; )
#define for1(i, n) for (auto i = 1; i <= (n); ++i)
#define forab(i, a, b) for (auto i = (a); i <= (b); ++i)
#define forit(it, a) for (auto it = (a); it != (a).end(); ++it)
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define pb(a) push_back(a)
#define ppb(a) pop_back(a)
#define fi first
#define se second

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
  for1(t, testcases) {
      solve(t);
  }
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
