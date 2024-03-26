class B
{
public:

	static inline auto m_common_data = 0; // note: no problems here

public:

	int m_data = 0; // note: possible problem with multiple inheritance

}; // class B

class L : public /*virtual*/ B {}; // good: virtual inheritance
class R : public /*virtual*/ B {}; // good: virtual inheritance

class C : public L, public R {}; // note: possible diamond problem

int main()
{
	C c;

	c.m_common_data = 42;

//	c.m_data = 42; // error: ambiguous data member selection

	return 0;
}