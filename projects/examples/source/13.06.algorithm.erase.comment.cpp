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
            if (*current == '"') // note: ignore characters inside string literals
            {
                for (++current; !((*current == '"') && (*std::prev(current) != '\\')); ++current);
            }
                
            if (*current == '/') 
            {
                if (*std::next(current) == '/') // note: single-line comment
                {
                    auto last = std::next(current, 2);

                    for (; last != std::end(code) && *last != '\n'; ++last);

                    current = code.erase(current, last);
                }
                else if (*std::next(current) == '*') // note: multi-line comment
                {
                    auto last = std::next(current, 3);

                    for (; !((*last == '/') && (*std::prev(last) == '*')); ++last);

                    current = code.erase(current, ++last);
                }
            }

            if (current == std::end(code)) break;
        }

        std::fstream("result.txt", std::ios::out) << code;
    }
    else std::cerr << "invalid file stream\n";

	return 0;
}