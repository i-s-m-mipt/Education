#include <cassert>
#include <chrono>
#include <iostream>

//////////////////////////////////////////////////////////

int main()
{
	auto now_1 = std::chrono::system_clock::now();

//  ------------------------------------------------------

	std::chrono::zoned_time now_2("Europe/London", now_1);

	std::chrono::zoned_time now_3("Europe/Berlin", now_1);

	std::chrono::zoned_time now_4("Europe/Moscow", now_1);

//  ------------------------------------------------------

	std::cout << "main : now_1 = " << now_1 << '\n';

	std::cout << "main : now_2 = " << now_2 << '\n';

	std::cout << "main : now_3 = " << now_3 << '\n';

	std::cout << "main : now_4 = " << now_4 << '\n';
}