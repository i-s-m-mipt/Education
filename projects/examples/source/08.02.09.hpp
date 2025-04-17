////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

////////////////////////////////////////////////////////////////////////////////////////////

#include <mutex>
#include <string>

////////////////////////////////////////////////////////////////////////////////////////////

#include <boost/noncopyable.hpp>
#include <boost/python.hpp>

////////////////////////////////////////////////////////////////////////////////////////////

class Python : private boost::noncopyable
{
public :

	Python() { acquire(); }

   ~Python() { release(); }

//  ----------------------------------------------------------------------------------------

	auto const & local() const
	{
		return m_local;
	}

//  ----------------------------------------------------------------------------------------

	static auto exception()
	{
		PyObject * error, * value, * stack;

	//  ------------------------------------------------------------------------------------

		PyErr_Fetch             (&error, &value, &stack);

		PyErr_NormalizeException(&error, &value, &stack);

	//  ------------------------------------------------------------------------------------

		boost::python::handle <> handler_1(boost::python::allow_null(value));

		boost::python::handle <> handler_2(error);

	//  ------------------------------------------------------------------------------------

		if (handler_1)
		{
			return boost::python::extract < std::string > (boost::python::str(handler_1))();
		}
		else
		{
			return boost::python::extract < std::string > (boost::python::str(handler_2))();
		}
	}

private :

	void acquire()
	{
		std::call_once(s_flag, Py_Initialize);

		s_mutex.lock();
			
		s_state = PyGILState_Ensure();

		m_local = boost::python::import("__main__").attr("__dict__");

		boost::python::exec("import sys\nsys.path.append(\".\")", m_local, m_local);
	}

//  ----------------------------------------------------------------------------------------

	void release()
	{
		PyGILState_Release(s_state);
		
		s_mutex.unlock();
	}

//  ----------------------------------------------------------------------------------------

	boost::python::api::object m_local;

//  ----------------------------------------------------------------------------------------

	static inline std::once_flag s_flag;

	static inline std::mutex s_mutex;
	
	static inline PyGILState_STATE s_state;
};

////////////////////////////////////////////////////////////////////////////////////////////