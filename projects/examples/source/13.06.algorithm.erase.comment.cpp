#include <filesystem>
#include <iostream>
#include <iterator>
#include <fstream>
#include <string>

int main()
{
	if (std::fstream fin("13.07.algorithm.erase.comment.test.txt", std::ios::in); fin)
    {
        std::string code { std::istreambuf_iterator < char > (fin),
		                   std::istreambuf_iterator < char > (   ) } ;

        for (auto current = std::begin(code); current != std::end(code); ++current) 
        {
            if (*current == '\'')
            {
                for (++current; !((*current == '\'') && (*std::prev(current) != '\\')); ++current);
            }

            if (*current == '"')
            {
                for (++current; !((*current == '"') && (*std::prev(current) != '\\')); ++current);
            }
                
            if (*current == '/') 
            {
                if (*std::next(current) == '/')
                {
                    auto last = std::next(current, 2);

                    for (; last != std::end(code) && *last != '\n'; ++last);

                    current = code.erase(current, last);
                }
                else if (*std::next(current) == '*')
                {
                    auto last = std::next(current, 3);

                    for (; !((*last == '/') && (*std::prev(last) == '*')); ++last);

                    current = code.erase(current, ++last);
                }
            }

            if (current == std::end(code)) break;
        }

        constexpr auto result = "13.07.algorithm.erase.comment.result.txt";

        std::fstream(result, std::ios::out) << code;

        std::cout << "Enter any character to continue: "; char c{}; std::cin >> c;

        std::filesystem::remove(result);
    }
    else std::cerr << "invalid file stream\n";

	return 0;
}