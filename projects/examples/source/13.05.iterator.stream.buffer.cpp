#include <iostream>
#include <iterator>

int main()
{
	std::istreambuf_iterator < char > istreambuf_iterator(std::cin);

	std::istreambuf_iterator < char > end;

	std::ostreambuf_iterator < char > ostreambuf_iterator(std::cout);

	while (istreambuf_iterator != end) 
	{
		*ostreambuf_iterator++ = *istreambuf_iterator++;
	}

	return 0;
}