# Vim Snippets for Competitive Programming
Write your snippets for competitive programming (CodeJam, Codeforces, HackerCup, TopCoder, etc.) with all the flexibility of `UltiSnips`. Ensure they works correctly by writing your own unit tests using `gtest`.


## Installation

It is recommended to use [Vundle][vundle] to install this plugin (it's cleaner this way). You will also need [UltiSnips][ultisnips] to use these snippets. In your `.vimrc`:

    Plugin 'SirVer/ultisnips'         "required
    Plugin 'hav4ik/contest-snippets'  "that's all :)

Additionally, you might want to install [vim-snippets][vimsnips] for other useful snippets. I personally don't use it.


## Implemented algorithms

* **Number Theory**
  - GCD
  - GCD extended
  - Prive Sieve in 4 variations:
    - Returns a bool vector
    - Returns a factorization vector
    - Returns a vector of primes
    - Memory-optimized for large upper bound
  - Chinese theorem solver


## Writing and testing your own snippets

You can write your own snippets using `c` or `c++`, test them and convert them into [UltiSnips][ultisnips]-compatible snippets. To do that, you'll need to:

1.  Install [Google Test][gtest]:
    If you are using ubuntu, the easiest way is:

        $ sudo apt-get install libgtest-dev
        $ cd /usr/src/gtest
        $ sudo cmake CMakeList.txt
        $ sudo make
        $ sudo cp *.a /usr/local/lib

    Or, you may follow instructions from official [repository][gtest] to build and install [Google Test][gtest].

2.  Write your own snippets:

    Create your code file `src/snippets/my.cpp`. A minimal snippet might look as follows:

        ```c++
        // this header contains neccessary macros
        #include "common.hpp"

        // google test framework
        #include <gtest/gtest.h>

        // don't do that in serious projects, it's shit
        using namespace std;

        //     trigger   snips file   title        detailed description
        SNIPPET("pow", "my.snippets", "a^n", "calculates power in O(log n)")
        TABSTOP(1,int) fastpow(MIRROR(1,int) a, MIRROR(1,int) n) {
            MIRROR(1,int) res = 1;
            while(n)
                if (n & 1) { res *= a; --n; }
                else {a *= a; n >>= 1; }
            return res;
        }
        TABSTOP(0)
        TESTSNIPPET
        TEST(FastPower, CommonCases) {
            ASSERT_EQ(fastpow(2, 8), 256);
            ASSERT_EQ(fastpow(3, 7), 2187);
        }
        TEST(FastPower, EdgeCases) {
            ASSERT_EQ(fastpow(0, 0), 1);
        }
        ENDSNIPPET
        ```

    Compile, test and generate an [UltiSnips][ultisnips]-like snippet as follows:

        $ cmake CMakeLists.txt
        $ make

    Now, there should be a file `my.snippets` in the folder `UltiSnips/cpp/`, which will look as follows:

        ```
        snippet pow "fast power calculation             - calculates power in O(log n)"
        ${1,int} fastpow($1 a, $1 n) {
            $1 res = 1;
            while(n)
                if (n & 1) { res *= a; --n; }
                else {a *= a; n >>= 1; }
            return res;
        }
        $0
        ```

    It is very convenient to place a `$0` tabstop at the end of the method. For more about tabstops and mirros, please check the [UltiSnip's documentation][ultisnips-doc].


[vundle]: https://github.com/VundleVim/Vundle.vim
[ultisnips]: https://github.com/SirVer/ultisnips
[vimsnips]: https://github.com/honza/vim-snippets
[gtest]: https://github.com/google/googletest
[ultisnips-doc]: https://github.com/SirVer/ultisnips/blob/master/doc/UltiSnips.txt
