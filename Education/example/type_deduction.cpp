import std;

template < typename T >
void f_1(T t)
{
	// ...
}

template < typename T >
void f_2(T & t)
{
	// ...
}

template < typename T >
void f_3(const T & t)
{
	// ...
}

template < typename T >
void f_4(T && t)
{
	// ...
}

void g(int x)
{}

int main()
{
	int           x = 42;
	const int    cx = x;
	const int & rcx = cx;

	f_1(  x); // T -> int
	f_1( cx); // T -> int
	f_1(rcx); // T -> int

	const char * const ptr = "Hello";

	f_1(ptr); // T -> const char *

	const char str[] = "Hello";

	f_1(str); // T -> const char *

	f_1(  g); // T -> void (*) (int)

	f_2(  x); // T -> int
	f_2( cx); // T -> const int
	f_2(rcx); // T -> const int

	f_2(str); // T -> const char [6]

	f_2(  g); // T -> void (int)

	f_3(  x); // T -> int
	f_3( cx); // T -> int
	f_3(rcx); // T -> int

	f_4(  x); // T -> int &
	f_4( cx); // T -> const int &
	f_4(rcx); // T -> const int &
	f_4( 42); // T -> int

	return 0;
}