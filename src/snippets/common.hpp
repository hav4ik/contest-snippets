#pragma once
#include "../macros.hpp"


MACROSNIPPET("head", "skeleton.snippets", "Common", "commonly used i/o, algorithms, datastructures, and quick defines")
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

/// here goes additional headers or your program
TABSTOP(0)
TESTSNIPPET
TEST(CommonMacros, TestDefinitions) {
    vector<int> ground_truth, res;
    int k;

    // forn, pb
    ground_truth = {0, 1, 2, 3, 4}; res.clear(); k = 5;
    forn(j, k) res.pb(j);
    ASSERT_EQ(ground_truth, res);

    // for1, pb
    ground_truth = {1, 2, 3, 4, 5}; res.clear(); k = 5;
    for1(j, k) res.pb(j);
    ASSERT_EQ(ground_truth, res);

    // forab
    ground_truth = {2, 3, 4, 5, 6}; res.clear(); int a = 2, b = 6;
    forab(j, a, b) res.pb(j);
    ASSERT_EQ(ground_truth, res);
}
ENDMACROSNIPPET


MACROSNIPPET("head", "skeleton.snippets", "Geometry 2D", "Basic geometry operations and structs")
/// Vector 2D and operations
template<typename T> struct vec2 { T x, y; vec2(T u, T v): x(u), y(v) {}
    vec2<T>& operator= (const vec2<T>& a){ x=a.x; y=a.y; return *this; } };
template<typename T> bool operator== (const vec2<T>& a, const vec2<T>& b) { return b.x==a.x && b.y==a.y; }
template<typename T> vec2<T> operator+ (const vec2<T>& a, const vec2<T>& b) { return vec2<T>(a.x+b.x,a.y+b.y); }
template<typename T> vec2<T> operator- (const vec2<T>& a, const vec2<T>& b) { return vec2<T>(a.x-b.x,a.y-b.y); }
template<typename T> vec2<T> operator* (const vec2<T>& a, T b) { return vec2<T>(a.x*b,a.y*b); }
template<typename T> vec2<T> operator* (T a, const vec2<T>& b) { return vec2<T>(a*b.x,a*b.y); }
template<typename T> vec2<T> operator/ (const vec2<T>& a, T b) { return vec2<T>(a.x/b,a.y/b); }
template<typename T> inline T scalar(const vec2<T>& a, const vec2<T>& b) { return a.x*b.x+a.y*b.y; }
template<typename T> inline T dot(const vec2<T>& a, const vec2<T>& b) { return a.x*b.y-a.y*b.x; }
template<typename T> inline vec2<T> rot(const vec2<T>& v, double theta, const vec2<T>& anchor=vec2<T>(T(0), T(0)))
{ vec2<T> t = v - anchor; return vec2<T>(t.x*cos(theta)-t.y*sin(theta),t.x*sin(theta)+t.y*cos(theta)); }
typedef vec2<int> vec2i; typedef vec2<float> vec2f; typedef vec2<double> vec2d;

TABSTOP(0)
TESTSNIPPET
TEST(Geometry2D, SimpleOperations) {
    vec2i a(1, 2), b(3, 4);
    ASSERT_EQ(a == vec2i(1, 2), true);      // operator==(vec2<T>, vec2<T>)
    ASSERT_EQ(a + b, vec2i(4, 6));          // operator+ (vec2<T>, vec2<T>)
    ASSERT_EQ(a - b, vec2i(-2, -2));        // operator- (vec2<T>, vec2<T>)
    ASSERT_EQ(a * 2, vec2i(2, 4));          // operator* (vec2<T>, T)
    ASSERT_EQ(2 * a, vec2i(2, 4));          // operator* (T, vec2<T>)
    ASSERT_EQ(a / 2, vec2i(0, 1));          // operator/ (vec2<T>, T)
    ASSERT_EQ(scalar(a, b), 11);            // scalar product
    ASSERT_EQ(dot(a, b), -2);               // dot product
    ASSERT_EQ(rot(a,M_PI/2.),vec2i(-2,1));  // rotation (with default anchor {0,0})
}
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
