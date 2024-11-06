#if (!defined(FUNCTION))
#  if (defined(_MSC_VER) || defined(__GNUC__))
#    define FUNCTION __FUNCTION__
#  else
#    define FUNCTION __func__
#  endif
#else
#  error "invalid macro definition"
#endif

#include <cstdint>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <iostream>
#include <iterator>
#include <mutex>
#include <random>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>
#include <unordered_set>
#include <utility>

#include <boost/noncopyable.hpp>
#include <boost/python.hpp>

//  ================================================================================================

class Python : private boost::noncopyable
{
public:

	Python() { acquire(); }
   ~Python() { release(); }

private:

	void acquire()
	{
		std::call_once
		(
			s_status, []() 
			{
				if (!Py_IsInitialized()) 
				{
					Py_Initialize();

					auto working_directory = std::filesystem::absolute(".").string().c_str();

					auto system_path = PySys_GetObject("path");

					PyList_Insert(system_path, 0, PyUnicode_FromString(working_directory));
				}
			}
		);

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

public:

	const auto & local() const
	{
		return m_local;
	}

//  ------------------------------

	static std::string exception()
	{
		PyObject * error;
		PyObject * value;
		PyObject * stack;

		PyErr_Fetch             (&error, &value, &stack);
		PyErr_NormalizeException(&error, &value, &stack);

		boost::python::handle <> handle_error(error);

		boost::python::handle <> handle_value(boost::python::allow_null(value));
		boost::python::handle <> handle_stack(boost::python::allow_null(stack));

		return boost::python::extract < std::string > 
		(
			handle_value ? boost::python::str(handle_value) : 
					   	   boost::python::str(handle_error)
		);
	}

private:

	static inline std::once_flag s_status;

	static inline std::mutex s_mutex;
	
	static inline PyGILState_STATE s_state;

//  ---------------------------------------

	boost::python::api::object m_local;
};

//  ================================================================================================

auto make_dictionary(std::size_t size, std::size_t length)
{
	std::random_device device;

    std::mt19937_64 engine(device());

	std::uniform_int_distribution <> distribution(97, 122);
	
	std::set < std::string > dictionary;
    
	for (std::string word(length, '_'); std::size(dictionary) < size; dictionary.insert(word))
    {
        for (auto & element : word) 
		{
			element = distribution(engine);
		}
    }

	return dictionary;
}

//  ================================================================================================

std::size_t hash(std::string_view string)
{
	std::uint32_t hash = std::size(string);

	for (const auto element : string)
	{
		hash = ((hash << 5) ^ (hash >> 27)) ^ element;
	}

	return hash;
}

//  ================================================================================================

int main()
{
    Python python;

//  ----------------------------------------------------------------------------------------

	try
    {
        boost::python::exec("from script import factorial", python.local(), python.local());
		
		auto result = python.local()["factorial"](100);
		
		std::cout << "100! = " << boost::python::extract < std::string > (result)() << '\n';
	}
	catch (const boost::python::error_already_set &)
	{
		std::cerr << "main : " << Python::exception() << '\n';
	}

//  ----------------------------------------------------------------------------------------

    auto size = 1'000'000uz;

    std::unordered_set < std::size_t > hashes; auto index = 0uz; std::string points;

    for (const auto & word : make_dictionary(size + 1, 10))
    {
        if (hashes.insert(hash(word)); index++ % (size / 50) == 0)
        {
            points += (std::to_string(index - 1) + ',');

            points += (std::to_string(index - std::size(hashes)) + ',');
        }
    }

    points.pop_back();

//  ----------------------------------------------------------------------------------------

	try
	{
		boost::python::exec("from script import make_plot", python.local(), python.local());

		python.local()["make_plot"](points.c_str(), "hash");
    }
    catch (const boost::python::error_already_set &)
	{
		std::cerr << "main : " << Python::exception() << '\n';
	}
}