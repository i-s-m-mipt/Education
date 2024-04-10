#include <iostream>
#include <string>

template < typename ... Ts > class Tuple;

template < > class Tuple < > { };

template < typename T, typename ... Ts > class Tuple < T, Ts ... >
{
private:

	T head;
	Tuple < Ts ... > tail;

public:
	Tuple() { }

	Tuple(T const& head, Tuple < Ts ... > const& tail) : head(head), tail(tail) {}

	template < typename VT, typename ... VTs, typename = std::enable_if_t < sizeof ... (VTs) == sizeof ... (Ts) > >
	Tuple(VT&& vhead, VTs&& ... vtail) : head(std::forward < VT > (vhead)),	tail(std::forward < VTs > (vtail) ...) 	{}

	template < typename VT, typename ... VTs, typename = std::enable_if_t < sizeof ... (VTs) == sizeof ... (Ts) > >
	Tuple(Tuple < VT, VTs ... > const& other) :	head(other.getHead()), tail(other.getTail()) {}

	T& getHead() { return head;	}

	T const& getHead() const { return head; }

	Tuple < Ts ... >& getTail() { return tail;	}

	Tuple < Ts ... > const& getTail() const	{ return tail; }
};

// =================================================================================================

template < unsigned N >
struct TupleGet
{
	template < typename T, typename ... Ts > static auto apply(Tuple < T, Ts ...> const& t)
	{
		return TupleGet < N - 1 > ::apply(t.getTail());
	}
};

template < > struct TupleGet < 0 >
{
	template < typename T, typename ... Ts >
	static T const& apply(Tuple < T, Ts ... > const& t)
	{
		return t.getHead();
	}
};

template < unsigned N, typename ... Ts > auto get(Tuple < Ts ... > const& t)
{
	return TupleGet < N > ::apply(t);
}

// =================================================================================================

template < typename ... Ts > auto makeTuple(Ts&& ... elems)
{
	return Tuple < std::decay_t < Ts > ... > (std::forward < Ts > (elems) ...);
}

// =================================================================================================

bool operator==(Tuple < > const&, Tuple < > const&)
{
	return true;
}

template < typename T1, typename ... Ts1, typename T2, typename ... Ts2,
	typename = std::enable_if_t < sizeof ... (Ts1) == sizeof... (Ts2) > >
bool operator==(Tuple < T1, Ts1 ... > const& lhs, Tuple < T2, Ts2 ... > const& rhs)
{
	return (lhs.getHead() == rhs.getHead() && lhs.getTail() == rhs.getTail());
}

template < typename T1, typename ... Ts1, typename T2, typename ... Ts2,
	typename = std::enable_if_t < sizeof ... (Ts1) == sizeof... (Ts2) > >
bool operator!=(Tuple < T1, Ts1 ... > const& lhs, Tuple < T2, Ts2 ... > const& rhs)
{
	return (!operator==(lhs, rhs));
}

std::strong_ordering operator<=>(Tuple < > const&, Tuple < > const&)
{
	return std::strong_ordering::equivalent;
}

template < typename T1, typename ... Ts1, typename T2, typename ... Ts2,
		   typename = std::enable_if_t < sizeof ... (Ts1) == sizeof... (Ts2) > >
std::strong_ordering operator<=>(Tuple < T1, Ts1 ... > const& lhs, Tuple < T2, Ts2 ... > const& rhs)
{
	if (lhs.getHead() == rhs.getHead())
		return lhs.getTail() <=> rhs.getTail();
	else if (lhs.getHead() < rhs.getHead())
		return std::strong_ordering::less;
	else
		return std::strong_ordering::greater;
}

// =================================================================================================

void printTuple(std::ostream& stream, Tuple < > const&, bool isFirst = true)
{
	stream << (isFirst ? '(' : ')');
}

template < typename T, typename ... Ts > void printTuple(std::ostream& stream, Tuple < T, Ts ... > const& t, bool isFirst = true)
{
	stream << (isFirst ? "(" : ", ");
	stream << t.getHead();
	printTuple(stream, t.getTail(), false);
}

template < typename ... Ts > std::ostream& operator<<(std::ostream& stream, Tuple < Ts ... > const& t)
{
	printTuple(stream, t);
	return stream;
}

// =================================================================================================

int main()
{
	auto t1 = makeTuple(1, 3.14, std::string("hello"));
	Tuple < int, double, std::string > t2 { 1, 1.41, "Hello, World!" };
	std::cout << t1 << '\n' << t2 << std::endl;
	std::cout << get < 2 > (t1) << std::endl;
	std::cout << std::boolalpha << (t1 < t2) << " " << (t1 != t2) << std::endl;

	return 0;
}