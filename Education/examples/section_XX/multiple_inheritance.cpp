import std;

class Base
{
public:

	static inline int m_common_data = 0; // note: no problems here

public:

	int m_data = 0;
};

class Left : public /*virtual*/ Base // good: virtual inheritance
{};

class Right : public /*virtual*/ Base // good: virtual inheritance
{};

class Central : public Left, public Right // note: avoid multiple inheritance
{};

int main()
{
	Central central;

	central.m_common_data = 42;

//	central.m_data = 42; // error: ambiguous data member selection

	return 0;
}