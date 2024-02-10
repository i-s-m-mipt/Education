#include "python_wrapper.hpp"

namespace solution::shared
{
	void Python::acquire()
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
		catch ([[maybe_unused]] const boost::python::error_already_set & error)
		{
			throw std::runtime_error(Python::exception());
		}
	}

	void Python::release()
	{
		try
		{
			PyGILState_Release(state); mutex.unlock();
		}
		catch ([[maybe_unused]] const boost::python::error_already_set & error)
		{
			throw std::runtime_error(Python::exception());
		}
	}

	[[nodiscard]] std::string Python::exception() noexcept
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
		catch ([[maybe_unused]] const boost::python::error_already_set & error)
		{
			catch_handler(FUNCTION, "invalid exception");
		}
		catch (const std::exception & exception)
		{
			catch_handler(FUNCTION, exception.what());
		}

		return "unknown exception";
	}

} // namespace solution::shared