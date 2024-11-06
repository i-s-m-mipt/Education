#include <filesystem>
#include <iostream>
#include <iterator>
#include <fstream>
#include <string>

void transform(const std::string & path_1, const std::string & path_2)
{
    if (std::fstream fin(path_1, std::ios::in); fin)
    {
        std::string code 
        { 
            std::istreambuf_iterator < char > (fin),
		    std::istreambuf_iterator < char > (   ) 
        };

        for (auto current = std::begin(code); current != std::end(code); ++current) 
        {
            if (*current == '\'')
            {
                for (++current; !((*current == '\'') && (*std::prev(current) != '\\')); ++current);
            }

            if (*current == '\"')
            {
                for (++current; !((*current == '\"') && (*std::prev(current) != '\\')); ++current);
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

            if (current == std::end(code)) 
            {
                break;
            }
        }

        if (std::fstream fout(path_2, std::ios::out); fout)
        {
            fout << code;
        }
        else 
        {
            std::cerr << "main : invalid file stream\n";
        }
    }
    else 
    {
        std::cerr << "main : invalid file stream\n";
    }
}

int main()
{
    auto path_1 = "13.07.algorithm.erase.comment.source.txt";
	auto path_2 = "13.07.algorithm.erase.comment.result.txt";

    transform(path_1, path_2);

    std::cout << "Enter any character to continue : "; char c; std::cin >> c;

    std::filesystem::remove(path_2);
}