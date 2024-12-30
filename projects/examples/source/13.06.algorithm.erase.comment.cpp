#include <exception>
#include <filesystem>
#include <ios>
#include <iostream>
#include <iterator>
#include <fstream>
#include <stdexcept>
#include <string>

void transform(const std::string & path_1, const std::string & path_2)
{
    if (std::fstream fin(path_1, std::ios::in); fin)
    {
        std::istreambuf_iterator < char > begin(fin), end;

        std::string code(begin, end);

        for (auto current = std::begin(code); current != std::end(code); ++current) 
        {
            if (*current == '\'')
            {
                for (++current; !(*current == '\'' && *std::prev(current) != '\\'); ++current);
            }

            if (*current == '\"')
            {
                for (++current; !(*current == '\"' && *std::prev(current) != '\\'); ++current);
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

                    for (; !(*last == '/' && *std::prev(last) == '*'); ++last);

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
            throw std::runtime_error("invalid stream");
        }
    }
    else 
    {
        throw std::runtime_error("invalid stream");
    }
}

int main()
{
    auto path_1 = "13.07.algorithm.erase.comment.source.txt";
	auto path_2 = "13.07.algorithm.erase.comment.result.txt";

    transform(path_1, path_2);

    std::cout << "main : enter char to continue : "; char c; std::cin >> c;

    std::filesystem::remove(path_2);
}