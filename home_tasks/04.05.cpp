#include <type_traits>

template<int N>
struct Fibonacci {
    static_assert(N >= 0, "N must be non-negative");
    static_assert(N <= 45, "N is too large, would cause integer overflow");
    
    static const int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

template<>
struct Fibonacci<0> {
    static const int value = 0;
};

template<>
struct Fibonacci<1> {
    static const int value = 1;
};

template<int N>
constexpr int Fibonacci_v = Fibonacci<N>::value;

static_assert(Fibonacci_v<0> == 0, "F(0) should be 0");
static_assert(Fibonacci_v<1> == 1, "F(1) should be 1");
static_assert(Fibonacci_v<2> == 1, "F(2) should be 1");
static_assert(Fibonacci_v<3> == 2, "F(3) should be 2");
static_assert(Fibonacci_v<4> == 3, "F(4) should be 3");
static_assert(Fibonacci_v<5> == 5, "F(5) should be 5");
static_assert(Fibonacci_v<6> == 8, "F(6) should be 8");
static_assert(Fibonacci_v<7> == 13, "F(7) should be 13");
static_assert(Fibonacci_v<8> == 21, "F(8) should be 21");
static_assert(Fibonacci_v<9> == 34, "F(9) should be 34");
static_assert(Fibonacci_v<10> == 55, "F(10) should be 55");
static_assert(Fibonacci_v<20> == 6765, "F(20) should be 6765");
static_assert(Fibonacci_v<45> == 1134903170, "F(45) should be 1134903170");

int main() {
    return 0;
}