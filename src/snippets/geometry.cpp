#include "common.hpp"


MACROSNIPPET("head", "skeleton.snippets", "Geometry 2D", "Basic geometry operations and structs")
/// Vector 2D and operations
template<typename T> struct vec2 {
    T x, y; vec2(T u, T v): x(u), y(v) {}
    vec2<T>& operator= (const vec2<T>& a) { 
        x=a.x; y=a.y; return *this; 
    } 
};
template<typename T> bool operator== (const vec2<T>& a, const vec2<T>& b) { return b.x==a.x && b.y==a.y; }
template<typename T> vec2<T> operator+ (const vec2<T>& a, const vec2<T>& b) { return vec2<T>(a.x+b.x,a.y+b.y); }
template<typename T> vec2<T> operator- (const vec2<T>& a, const vec2<T>& b) { return vec2<T>(a.x-b.x,a.y-b.y); }
template<typename T> vec2<T> operator* (const vec2<T>& a, T b) { return vec2<T>(a.x*b,a.y*b); }
template<typename T> vec2<T> operator* (T a, const vec2<T>& b) { return vec2<T>(a*b.x,a*b.y); }
template<typename T> vec2<T> operator/ (const vec2<T>& a, T b) { return vec2<T>(a.x/b,a.y/b); }
template<typename T> inline T scalar(const vec2<T>& a, const vec2<T>& b) { return a.x*b.x+a.y*b.y; }
template<typename T> inline T dot(const vec2<T>& a, const vec2<T>& b) { return a.x*b.y-a.y*b.x; }
template<typename T> inline vec2<T> rot(const vec2<T>& v, double theta, const vec2<T>& anchor=vec2<T>(T(0), T(0))) { 
    vec2<T> t = v - anchor; 
    return vec2<T>(t.x*cos(theta)-t.y*sin(theta),t.x*sin(theta)+t.y*cos(theta)); 
}
typedef vec2<int> vec2i;
typedef vec2<float> vec2f;
typedef vec2<double> vec2d;

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


