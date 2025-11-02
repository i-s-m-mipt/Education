class Vector
{
public :

	Vector() : m_array(nullptr), m_size(0) 
	{
		std::print("Vector:: Vector (1)\n");
	}

//  --------------------------------------------------------------------------------

	Vector(std::initializer_list < int > list) : m_size(std::size(list))
	{
		std::print("Vector:: Vector (2)\n");

		m_array = m_size ? new int[m_size]{} : nullptr;

		std::ranges::copy(list, m_array);
	}

//  --------------------------------------------------------------------------------

	Vector(Vector const & other) : m_size(other.m_size) 
	{
		std::print("Vector:: Vector (3)\n");

		m_array = m_size ? new int[m_size]{} : nullptr;

		std::ranges::copy(other.m_array, other.m_array + other.m_size, m_array);
	}

//  --------------------------------------------------------------------------------

	Vector(Vector && other)
	: 
		m_array(std::exchange(other.m_array, nullptr)), 
		
		m_size (std::exchange(other.m_size,  0      ))
	{
		std::print("Vector:: Vector (4)\n");
	}

//  --------------------------------------------------------------------------------

   ~Vector()
	{
		std::print("Vector::~Vector\n");

		delete[] m_array;
	}

	auto & operator=(Vector other)
	{
		std::print("Vector::operator= (4)\n");

		swap(other);

		return *this;
	}

//  --------------------------------------------------------------------------------

	void swap(Vector & other)
	{
		std::swap(m_array, other.m_array);
		
		std::swap(m_size,  other.m_size );
	}

private :

	int * m_array = nullptr;

	std::size_t m_size = 0;
};