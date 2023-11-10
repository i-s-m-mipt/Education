class Base
{
public:

	static inline auto m_common_data = 0; // note: no problems here

public:

	int m_data = 0; // note: possible problem with multiple inheritance

}; // class Base

class L : public /*virtual*/ Base {}; // good: virtual inheritance
class R : public /*virtual*/ Base {}; // good: virtual inheritance

class C : public L, public R {}; // note: possible diamond problem

int main()
{
	C c;

	c.m_common_data = 42;

//	c.m_data = 42; // error: ambiguous data member selection

	return 0;
}