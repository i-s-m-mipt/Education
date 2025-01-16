#include <cstdint>
#include <cstddef>
#include <iostream>
#include <mutex>
#include <random>
#include <set>
#include <string>
#include <thread>
#include <unordered_set>

using namespace std::literals;

#include <boost/noncopyable.hpp>
#include <boost/python.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////

class Python : private boost::noncopyable
{
public:

	Python() { acquire(); }

   ~Python() { release(); }

//  ------------------------------------------------------------------------------------------

	const auto & local() const
	{
		return m_local;
	}

//  ------------------------------------------------------------------------------------------

	static auto exception()
	{
		PyObject * error, * value, * stack;

		PyErr_Fetch             (&error, &value, &stack);

		PyErr_NormalizeException(&error, &value, &stack);

		boost::python::handle <> handle_error(error);

		boost::python::handle <> handle_value(boost::python::allow_null(value));

		boost::python::handle <> handle_stack(boost::python::allow_null(stack));

		auto result =  
		(
			handle_value ? boost::python::str(handle_value) : boost::python::str(handle_error)
		);

		return boost::python::extract < std::string > (result)();
	}

private:

	void acquire()
	{
		std::call_once(s_status, [](){ Py_Initialize(); });

		s_mutex.lock(); 
			
		s_state = PyGILState_Ensure();

		m_local = boost::python::import("__main__").attr("__dict__");

		boost::python::exec("import sys\nsys.path.append(\".\")", m_local, m_local);
	}

	void release()
	{
		PyGILState_Release(s_state); 
		
		s_mutex.unlock();
	}

//  ------------------------------------------------------------------------------------------

	boost::python::api::object m_local;

//  ------------------------------------------------------------------------------------------

	static inline std::once_flag s_status;

	static inline std::mutex s_mutex;
	
	static inline PyGILState_STATE s_state;
};

//////////////////////////////////////////////////////////////////////////////////////////////

auto factorial(int x)
{
	Python python;

	try
	{
		boost::python::exec("from script import factorial", python.local(), python.local());
			
		return boost::python::extract < std::string > (python.local()["factorial"](x))();
	}
	catch (const boost::python::error_already_set &)
	{
		std::cerr << "factorial : " << Python::exception() << '\n';

		return ""s;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////

auto make_dictionary(std::size_t size, std::size_t length)
{
	std::set < std::string > dictionary;

	std::string word(length, '_');

	std::default_random_engine engine;

	std::uniform_int_distribution distribution(97, 122);
    
	while (std::size(dictionary) < size)
    {
        for (auto & element : word) 
		{
			element = distribution(engine);
		}

		dictionary.insert(word);
    }

	return dictionary;
}

//////////////////////////////////////////////////////////////////////////////////////////////

auto hash(const std::string & string) -> std::size_t
{
	std::uint32_t hash = std::size(string);

	for (auto element : string)
	{
		hash = hash << 5 ^ hash >> 27 ^ element;
	}

	return hash;
}

//////////////////////////////////////////////////////////////////////////////////////////////

void make_plot(const std::string & string)
{
	Python python;

	try
	{
		boost::python::exec("from script import make_plot", python.local(), python.local());

		python.local()["make_plot"](string.c_str(), "hash");
	}
	catch (const boost::python::error_already_set &)
	{
		std::cerr << "make_plot : " << Python::exception() << '\n';
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		auto result = factorial(100);

		std::cout << "main : result = " << result << '\n';
	}

//  ------------------------------------------------------------------------

	{
		auto size = 1'000'000uz, index = 0uz;
	
		std::unordered_set < std::size_t > hashes; 
		
		std::string points;

		for (const auto & word : make_dictionary(size + 1, 10))
		{
			hashes.insert(hash(word));
			
			if (index++ % (size / 50) == 0)
			{
				points += (std::to_string(index - 1) + ',');

				points += (std::to_string(index - std::size(hashes)) + ',');
			}
		}

		points.pop_back();

		make_plot(points);
	}
}