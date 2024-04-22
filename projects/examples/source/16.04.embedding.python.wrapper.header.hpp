#pragma once

#if (!defined(FUNCTION))
#  if (defined(_MSC_VER) || defined(__GNUC__))
#    define FUNCTION __FUNCTION__
#  else
#    define FUNCTION __func__
#  endif
#else
#  error "invalid macro definition"
#endif

#include <exception>
#include <filesystem>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>
#include <utility>

#include <boost/noncopyable.hpp>
#include <boost/python.hpp>

namespace solution::shared
{
	class Python : private boost::noncopyable
	{
	public:

		Python()          {       acquire();                                 }
	   ~Python() noexcept { try { release(); } catch (...) { std::abort(); } }

	private:

		void acquire();

		void release();

	public:

		[[nodiscard]] const boost::python::api::object & global() const noexcept
		{
			return m_global;
		}

	public:

		[[nodiscard]] static std::string exception() noexcept;

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

} // namespace solution::shared