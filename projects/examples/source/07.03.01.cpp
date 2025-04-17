///////////////////////////////////////////////////////////////

#include <format>
#include <iostream>
#include <stacktrace>

///////////////////////////////////////////////////////////////

void test_v1()
{
    for (auto const & entry : std::stacktrace::current())
    {
        std::cout << "test_v1 : entry : ";

        if (auto file = entry.source_file(); !std::empty(file))
        {
            std::cout << file << " : ";
        }

        if (auto line = entry.source_line(); line > 0)
        {
            std::cout << std::format("{:0>3}", line) << " : ";
        }

        std::cout << entry.description() << '\n';
    }
}

///////////////////////////////////////////////////////////////

void test_v2() { test_v1(); }

void test_v3() { test_v2(); }

///////////////////////////////////////////////////////////////

int main()
{
    test_v3();
}

///////////////////////////////////////////////////////////////