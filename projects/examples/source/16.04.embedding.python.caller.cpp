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

	Python()          {       acquire();                                 }
   ~Python() noexcept { try { release(); } catch (...) { std::abort(); } }

private:

	void acquire()
	{
		try
		{
			std::call_once(is_initialized_once, []() 
			{
				if (!Py_IsInitialized()) 
				{
					Py_Initialize();

					auto working_directory = std::filesystem::absolute("./");

					auto system_path = PySys_GetObject("path");

					PyList_Insert(system_path, 0, PyUnicode_FromString(working_directory.string().c_str()));
				}
			});

			mutex.lock(); state = PyGILState_Ensure();

			m_global = boost::python::import("__main__").attr("__dict__");
		}
		catch (const boost::python::error_already_set &)
		{
			throw std::runtime_error(Python::exception());
		}
	}

	void release()
	{
		try
		{
			PyGILState_Release(state); mutex.unlock();
		}
		catch (const boost::python::error_already_set &)
		{
			throw std::runtime_error(Python::exception());
		}
	}

public:

	[[nodiscard]] const boost::python::api::object & global() const noexcept
	{
		return m_global;
	}

	[[nodiscard]] static std::string exception() noexcept
	{
		try
		{
			PyObject * error;
			PyObject * value;
			PyObject * stack;

			PyErr_Fetch             (&error, &value, &stack);
			PyErr_NormalizeException(&error, &value, &stack);

			boost::python::handle <> handle_error(error);

			boost::python::handle <> handle_value(boost::python::allow_null(value));
			boost::python::handle <> handle_stack(boost::python::allow_null(stack));

			std::string message = boost::python::extract < std::string > (handle_value ? 
				boost::python::str(handle_value) : boost::python::str(handle_error));

			return message;
		}
		catch (const boost::python::error_already_set &)
		{
			catch_handler(FUNCTION, "invalid exception");
		}
		catch (const std::exception & exception)
		{
			catch_handler(FUNCTION, exception.what());
		}

		return "unknown exception";
	}

private:

	static void catch_handler(std::string_view scope, std::string_view message) noexcept
	{
		try { std::cerr << scope << " : " << message << '\n'; } catch (...) {}
	}

private:

	static inline std::once_flag is_initialized_once;

	static inline std::mutex       mutex;
	static inline PyGILState_STATE state; // note: global interpreter locker

private:

	boost::python::api::object m_global;

}; // class Python : private boost::noncopyable

//  ================================================================================================

std::set < std::string > make_random_words(std::size_t size, const std::size_t length)
{
    std::mt19937_64 engine(std::random_device{}());

	std::uniform_int_distribution <> distribution(97, 122);
	
	std::set < std::string > words;
    
	for (std::string word(length, '_'); std::size(words) < size; words.insert(word))
    {
        for (auto & letter : word) letter = distribution(engine);
    }

	return words;
}

//  ================================================================================================

std::size_t hash_DEK(std::string_view string) // note: Donald E. Knuth implementation
{
	std::uint32_t hash = std::size(string); // note: as with x86 build to make collisions

	for (const auto letter : string)
	{
		hash = ((hash << 5) ^ (hash >> 27)) ^ letter;
	}

	return hash;
}

//  ================================================================================================

int main()
{
    try
    {
        Python python;

//  ================================================================================================

        boost::python::exec("from script import factorial", python.global(), python.global());
		
		std::cout << boost::python::extract < std::string > (
            python.global()["factorial"](100))() << std::endl; // note: outputs 100!

//  ================================================================================================

        const std::size_t size = 1'000'000, length = 10, step = size / 50;

        std::unordered_set < std::size_t > hashes; std::size_t index = 0; std::string points;

        for (const auto & word : make_random_words(size + 1, length))
        {
            if (hashes.insert(hash_DEK(word)); index++ % step == 0)
            {
                points += std::to_string(index - 1                ) + ',' + 
                          std::to_string(index - std::size(hashes)) + ',';
            }
        }

        points.pop_back(); // note: remove last comma in string

//  ================================================================================================

        boost::python::exec("from script import make_plot", python.global(), python.global());
		
		python.global()["make_plot"](points.c_str(), "DEK");
    }
    catch (const boost::python::error_already_set &)
	{
		std::cerr << Python::exception() << '\n';
	}
    catch (const std::exception & exception)
    {
        std::cerr << exception.what() << '\n';
    }
    
    return 0;
}