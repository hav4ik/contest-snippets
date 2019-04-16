#include "common.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>


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


SNIPPET("prime", "numbers.snippets", "Prime Sieve", "Generates bool vector with true on primes")
inline void prime_sieve(int n, vector<bool>& prime) {
  prime.resize(n + 1, true);
  prime[0] = prime[1] = false;
  for (int i = 2; i * 1ll * i <= n; ++i)
    if (prime[i])
      for (int j = i * i; j <= n; j += i) prime[j] = false;
}
TESTSNIPPET
TEST(PrimeSieve, SimpleCase) {
  vector<bool> p; prime_sieve(9, p);
  ASSERT_THAT(p, testing::ElementsAre(
        false, false, true, true, false, true, false, true, false, false));
}
ENDSNIPPET


SNIPPET("prime", "numbers.snippets", "Factoriz. Sieve", "Primes Sieve with factorization")
inline void factorization_sieve(int n, vector<int>& factor) {
  factor.resize(n + 1, 0);
  vector<int> pr;
  for (int i=2; i<=n; ++i) {
    if (factor[i] == 0) {
      factor[i] = i;
      pr.push_back (i);
    }
    for (int j=0; j<(int)pr.size() && pr[j]<=factor[i] && i*pr[j]<=n; ++j)
      factor[i * pr[j]] = pr[j];
  }
}
TESTSNIPPET
TEST(FactorizationSieve, SimpleCase) {
  vector<int> f; factorization_sieve(9, f);
  ASSERT_THAT(f, testing::ElementsAre(0, 0, 2, 3, 2, 5, 2, 7, 2, 3));
}
ENDSNIPPET


SNIPPET("prime", "numbers.snippets", "Prime Generator", "Generates a vector of primes")
inline void prime_generate(int n, vector<int>& primes) {
  vector<bool> bp(n + 1, true);
  bp[0] = bp[1] = false;
  for (int i = 2; i * 1ll * i <= n; ++i)
    if (bp[i])
      for (int j = i * i; j <= n; j += i) bp[j] = false;
  primes.reserve((int)log(n + 0.)); primes.clear();
  for (int i = 0; i < n; ++i)
    if (bp[i]) primes.push_back(i);
}
TESTSNIPPET
TEST(PrimeGeneratorSmall, SimpleCase) {
  vector<int> p; prime_generate(20, p);
  ASSERT_THAT(p, testing::ElementsAre(2, 3, 5, 7, 11, 13, 17, 19));
}
ENDSNIPPET


SNIPPET("prime", "numbers.snippets", "Prime Generator", "Generates a vector of primes (ONLY for n > 10^6")
const int pgen_block_size = TABSTOPWDEF(1,10000);
inline void prime_generate(int n, vector<int>& primes) {
  int nsqrt = (int) sqrt (n + .0);
  vector<bool> bp(nsqrt + 1, true), blp(pgen_block_size, true);
  bp[0] = bp[1] = false;
  for (int i = 2; i * 1ll * i <= nsqrt; ++i)
    if (bp[i])
      for (int j = i * i; j <= nsqrt; j += i) bp[j] = false;
  primes.reserve((int)log(n + .0)); primes.clear();
  for (int i = 0; i < nsqrt + 1; ++i)
    if (bp[i]) primes.push_back(i);
  for (int k=0, maxk=n/pgen_block_size; k<=maxk; ++k) {
    blp.assign(pgen_block_size, false);
    int start = k * pgen_block_size;
    for (int i=0; i<primes.size(); ++i) {
      int start_idx = (start + primes[i] - 1) / primes[i];
      int j = max(start_idx, 2) * primes[i] - start;
      for (; j<pgen_block_size; j+=primes[i])
        blp[j] = true;
    }
    if (k == 0)
      blp[0] = blp[1] = true;
    for (int i=0; i<pgen_block_size && start+i<=n; ++i)
      if (!blp[i])
        primes.push_back(start + i);
  }
}
TESTSNIPPET
TEST(PrimeGeneratorLarge, SimpleCase) {
  vector<int> p; prime_generate(997*997, p);
  vector<int> first_five(p.begin(), p.begin() + 5);
  vector<int> last_five(p.begin() + p.size() - 5, p.end());
  ASSERT_THAT(first_five, testing::ElementsAre(
        2, 3, 5, 7, 11));
  ASSERT_THAT(last_five, testing::ElementsAre(
        993943, 993961, 993977, 993983, 993997));
}
ENDSNIPPET


SNIPPET("chinese", "numbers.snippets", "Chinese Theorem", "Given {a_i = a % p_i}_1^k, restores a")
// Given a system of remainder equations:
//   a mod p0 = r0
//   ...
//   a mod pk = rk
// Restore the number a:
//   a = x1 + x2*p1 + x3*p1*p2 + ... + xk*p1*...*pk_1
TABSTOPWDEF(2,int) chinese_solver(
    const vector<TABSTOPWDEF(1,int)>& ps,
    const vector<MIRRORWDEF(1,int)>& as,
    vector<MIRRORWDEF(1,int)>& xs) {
  auto mul_inv = [](MIRRORWDEF(1,int) a, MIRRORWDEF(1,int) b) {
    MIRRORWDEF(1,int) b0(b), x0(0), x1(1);
    if (b == 1) return 1;
    while (a > 1) {
      MIRRORWDEF(1,int) q = a / b;
      MIRRORWDEF(1,int) amb = a % b;
      a = b, b = amb;
      MIRRORWDEF(1,int) xqx = x1 - q * x0;
      x1 = x0, x0 = xqx;
    }
    if (x1 < 0) x1 += b0;
    return x1;
  };
  int x, y; xs.resize(as.size());
  for (int i=0; i<as.size(); ++i) {
    xs[i] = as[i];
    for (int j=0; j<i; ++j) {
      MIRRORWDEF(1,int) r_ji = mul_inv(ps[j], ps[i]);
      xs[i] = r_ji * (xs[i] - xs[j]);
      xs[i] = xs[i] % ps[i];
      if (xs[i] < 0) xs[i] += ps[i];
    }
  }
  MIRRORWDEF(2,int) a(0);
  for (int i = 0; i < as.size(); ++i) {
    MIRRORWDEF(2,int) one(xs[i]);
    for (int j = 0; j < i; ++j)
      one *= ps[j];
    a += one;
  }
  return a;
}
TABSTOP(0)
TESTSNIPPET
TEST(ChineseTheoremSolver, SimpleTest) {
  vector<int> ps = {2, 3, 5, 7, 11}, as = {0, 1, 1, 1, 5}, xs;
  int a = chinese_solver(ps, as, xs);
  ASSERT_EQ(a, 1996);
}
ENDSNIPPET
