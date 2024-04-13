#include <iterator>
#include <fstream>
#include <string>

void erase_comments(std::string & code);

int main(int argc, char ** argv)
{
	std::fstream fin("test.txt", std::ios::in);

	std::string code {
		std::istreambuf_iterator < char > (fin),
		std::istreambuf_iterator < char > () };

	erase_comments(code);

	std::fstream fout("result.txt", std::ios::out);

	fout << code;

	system("pause");

	return EXIT_SUCCESS;
}

void erase_comments(std::string & code)
{
	for (auto current = std::begin(code); current != std::end(code); ++current) 
	{
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

		if (current == std::end(code))
		{
			break;
		}
	}
}