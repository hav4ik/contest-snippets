# contest-snippets
Vim snippets for competitive programming.


## Installation

It is recommended to use [Vundle][vundle] to install this plugin (it's cleaner this way). You will also need [UltiSnips][ultisnips] to use these snippets. In your `.vimrc`:

    Plugin 'SirVer/ultisnips'         "required
    Plugin 'hav4ik/contest-snippets'  "that's all :)

Additionally, you might want to install [vim-snippets][vimsnips] for other useful snippets. I personally don't use it.


## Writing and testing your own snippets

You can write your own snippets using `c` or `c++`, test them and convert them into [UltiSnips][ultisnips]-compatible snippets. To do that, you'll need to:

1. Install [Google Test][gtest]
   If you are using ubuntu, the easiest way is:

       $ sudo apt-get install libgtest-dev
       $ cd /usr/src/gtest
       $ sudo cmake CMakeList.txt
       $ sudo make
       $ sudo cp *.a /usr/local/lib

   Or, you may follow instructions from official [repository][gtest] to build and install [Google Test][gtest].

2. Write your own snippets
   A minimal snippet might look as follows:





[vundle]: https://github.com/VundleVim/Vundle.vim
[ultisnips]: https://github.com/SirVer/ultisnips
[vimsnips]: https://github.com/honza/vim-snippets
[gtest]: https://github.com/google/googletest
