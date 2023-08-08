import std;

int main()
{
    auto x = 1;

    decltype(x) y = x + 1;

    static_assert(std::is_same_v < decltype(x), decltype(y) >);

    decltype((x)) r = x;

    const auto & cx = x;

    auto z_1 = cx; // auto -> int

    decltype(auto) z_2 = cx; // decltype(auto) -> const int &

    auto f = [](auto a, auto b) { return a * b; };
    auto g = [](auto a, auto b) { return a * b; };

    static_assert(!std::is_same_v < decltype(f), decltype (g) >);

	return 0;
}