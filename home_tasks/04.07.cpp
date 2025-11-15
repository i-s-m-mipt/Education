#include <numeric>
#include <type_traits>

template<int N = 0, int D = 1>
struct Ratio {
    static_assert(D != 0, "Denominator cannot be zero");
    constexpr static int num = N;
    constexpr static int den = D;
};

template<typename R1, typename R2>
struct Sum {
    constexpr static auto num = R1::num * R2::den + R2::num * R1::den;
    constexpr static auto den = R1::den * R2::den;
    constexpr static auto gcd = std::gcd(num, den);
    using type = Ratio<num/gcd, den/gcd>;
};
template<typename R1, typename R2> using sum = typename Sum<R1, R2>::type;

template<typename R1, typename R2>
struct Mul {
    constexpr static auto num = R1::num * R2::num;
    constexpr static auto den = R1::den * R2::den;
    constexpr static auto gcd = std::gcd(num, den);
    using type = Ratio<num/gcd, den/gcd>;
};
template<typename R1, typename R2> using mul = typename Mul<R1, R2>::type;

template<typename R1, typename R2>
struct Sub {
    using type = sum<R1, Ratio<-R2::num, R2::den>>;
};
template<typename R1, typename R2> using sub = typename Sub<R1, R2>::type;

template<typename R1, typename R2>
struct DivOp {
    static_assert(R2::num != 0, "Division by zero");
    using type = mul<R1, Ratio<R2::den, R2::num>>;
};
template<typename R1, typename R2> using div_op = typename DivOp<R1, R2>::type;

template<typename T, typename R = Ratio<1>>
struct Duration {
    T x = T();
    constexpr Duration(T value) : x(value) {}
};

template<typename T1, typename R1, typename T2, typename R2>
constexpr auto operator+(const Duration<T1, R1>& a, const Duration<T2, R2>& b) {
    using R = sum<R1, R2>;
    auto value = a.x * R::den / R1::den * R1::num + b.x * R::den / R2::den * R2::num;
    return Duration<decltype(value), R>(value);
}

template<typename T1, typename R1, typename T2, typename R2>
constexpr auto operator-(const Duration<T1, R1>& a, const Duration<T2, R2>& b) {
    return a + Duration<T2, Ratio<-R2::num, R2::den>>(-b.x);
}

// Тесты
static_assert(std::is_same_v<sum<Ratio<1,2>, Ratio<1,3>>, Ratio<5,6>>);
static_assert(std::is_same_v<sub<Ratio<1,2>, Ratio<1,3>>, Ratio<1,6>>);
static_assert(std::is_same_v<mul<Ratio<1,2>, Ratio<2,3>>, Ratio<1,3>>);
static_assert(std::is_same_v<div_op<Ratio<1,2>, Ratio<2,3>>, Ratio<3,4>>);

int main() {
    constexpr Duration<int, Ratio<1,2>> a(1);
    constexpr Duration<int, Ratio<1,3>> b(2);
    constexpr auto c = a + b;
    constexpr auto d = a - b;
    static_assert(c.x == 7);
    return 0;
}