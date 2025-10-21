//////////////////////////////////////////////////////////

#include <chrono>
#include <print>

//////////////////////////////////////////////////////////

int main()
{
	auto now_1 = std::chrono::system_clock::now();

//  ------------------------------------------------------

	std::chrono::zoned_time now_2("Europe/London", now_1);

	std::chrono::zoned_time now_3("Europe/Berlin", now_1);

	std::chrono::zoned_time now_4("Europe/Moscow", now_1);

//  ------------------------------------------------------

	std::print("main : now_1 = {}\n", now_1);

	std::print("main : now_2 = {}\n", now_2);

	std::print("main : now_3 = {}\n", now_3);

	std::print("main : now_4 = {}\n", now_4);
}

//////////////////////////////////////////////////////////