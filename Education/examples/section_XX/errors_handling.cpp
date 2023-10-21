import std;

template < typename T >
[[maybe_unused]] void swap(T & a, T & b) noexcept
{
    static_assert(std::is_copy_constructible_v<T>,
        "swap requires copy constructible type");

    static_assert(std::is_nothrow_copy_constructible_v < T > &&
                  std::is_nothrow_copy_assignable_v    < T >,
        "swap requires nothrow copy constructible and assignable type");

    auto c = b; b = a; a = c;
}

int main()
{
    static_assert(2 + 2 == 4); // note: optional message string

    static_assert(sizeof(int) == 4, "required int size 4 bytes");

    return codes, errno, refs args, exceptions, custom exceptions, unions, 
        variant, if+while, assert, logger
        abort exit terminate

        uncaught exceptions, noexcept, destructors and constructors
        function catch blocks
        https ://www.learncpp.com/cpp-tutorial/function-try-blocks/
https://www.learncpp.com/cpp-tutorial/exception-dangers-and-downsides/
https://www.learncpp.com/cpp-tutorial/exception-specifications-and-noexcept/
https://www.learncpp.com/cpp-tutorial/stdmove_if_noexcept/
	return 0;
}