#pragma once
#include <gtest/gtest.h>

// Macro tools
#define MACRO_CAT_PRIMITIVE(A, B) A##B
#define MACRO_CAT(A, B) MACRO_CAT_PRIMITIVE(A, B)

// Snippets
#define SNIPPET(TRIGGER, SNIPPET_FILE, SHORT_DESC, LONG_DESC) \
    namespace MACRO_CAT(SNIPPET, __COUNTER__) {
#define TESTSNIPPET
#define ENDSNIPPET };

// Macros
#define MACROSNIPPET(TRIGGER, SNIPPET_FILE, SHORT_DESC, LONG_DESC)
#define ENDMACROSNIPPET

// Inline stuffs are wrapped into a class
#define INLINESNIPPET(TRIGGER, SNIPPET_FILE, SHORT_DESC, LONG_DESC) \
    SNIPPET(TRIGGER, SNIPPET_FILE, SHORT_DESC, LONG_DESC) \
    class wrapper {
#define ENDINLINESNIPPET }; ENDSNIPPET

// UltiSnips stuffs
#define TABSTOPWDEF(N,DEFVAL) DEFVAL
#define MIRROR(N,DEFVAL) DEFVAL
#define TABSTOP(N)
