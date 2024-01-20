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
#include <iomanip>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_map>

using namespace std::literals;

#include <boost/core/null_deleter.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/common.hpp>
#include <boost/log/core.hpp>
#include <boost/log/exceptions.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/support/exception.hpp>
#include <boost/log/utility/formatting_ostream.hpp>
#include <boost/log/utility/value_ref.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/make_shared.hpp>
#include <boost/noncopyable.hpp>
#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/shared_ptr.hpp>

namespace solution::shared
{
	class Logger : private boost::noncopyable
	{
	private:

		enum class Attribute
		{
			line,
			time,
			severity,
			thread,
			process,

		}; // enum class Attribute

	public:

		enum class Severity
		{
			empty,
			debug,
			trace,
			error,
			fatal,

		}; // enum class Severity

	private:

		using attributes_t = std::unordered_map < Attribute, std::pair < std::string, boost::log::attribute > > ;

		using severities_t = std::unordered_map < Severity, std::string_view > ;

	private:

		using status_t = std::once_flag;

		using logger_t = boost::log::sources::severity_logger_mt < Severity > ;

	private:

		using sink_t = boost::log::sinks::synchronous_sink < boost::log::sinks::text_file_backend > ;

	public:

		explicit Logger(const char * scope, bool has_trace = true) noexcept : m_scope(scope), m_has_trace(has_trace)
		{
			try
			{
				std::call_once(status, Logger::initialize);
			}
			catch (const std::exception & exception)
			{
				catch_handler(FUNCTION, exception.what()); std::abort();
			}

			if (m_has_trace) write(Severity::trace, "EXECUTION ... ");
		}

		~Logger() noexcept
		{
			if (m_has_trace) write(Severity::trace, "EXECUTION COMPLETE");
		}

	private:

		static void initialize();

		static boost::shared_ptr < sink_t > make_fout_sink();

		static void fout_formatter(const boost::log::record_view & record_view, boost::log::formatting_ostream & stream);

	public:

		[[nodiscard]] auto scope() const noexcept
		{
			return m_scope;
		}

	public:

		[[nodiscard]] static auto severity_as_string(Severity severity)
		{
			return severities.at(severity);
		}

	public:

		void write(Severity severity, const std::string & message) const noexcept;

	private:

		static void catch_handler(std::string_view scope, std::string_view message) noexcept
		{
			try { std::cerr << scope << " : " << message << '\n'; } catch (...) {}
		}

	private:

		static inline const auto separator = " : ";

	private:

		static inline const attributes_t attributes =
		{
			{ Logger::Attribute::line,     std::make_pair("line",    boost::log::attributes::counter < std::size_t > ()) },
			{ Logger::Attribute::time,     std::make_pair("time",    boost::log::attributes::utc_clock               ()) },
			{ Logger::Attribute::process,  std::make_pair("process", boost::log::attributes::current_process_id      ()) },
			{ Logger::Attribute::thread,   std::make_pair("thread",  boost::log::attributes::current_thread_id       ()) },
			{ Logger::Attribute::severity, std::make_pair(
				boost::log::aux::default_attribute_names::severity().string(), boost::log::attribute()) }
		};

		static inline const severities_t severities =
		{
			{ Logger::Severity::empty, "empty" },
			{ Logger::Severity::debug, "debug" },
			{ Logger::Severity::trace, "trace" },
			{ Logger::Severity::error, "error" },
			{ Logger::Severity::fatal, "fatal" }
		};

	private:

		static inline status_t status;
		static inline logger_t logger;

	private:

		const char* const m_scope;

	private:

		bool m_has_trace;

	}; // class Logger : private boost::noncopyable

	template < typename E > void catch_handler(Logger & logger, const std::exception & exception)
	{
		static_assert(std::is_base_of_v < std::exception, E >, "invalid exception type");

		logger.write(Logger::Severity::error, exception.what());

		throw E(logger.scope() + " exception"s);
	}

} // namespace solution::shared 

#define LOGGER_2(logger, has_trace) solution::shared::Logger logger(FUNCTION, has_trace)

#define LOGGER_1(logger) LOGGER_2(logger, true)

#if !BOOST_PP_VARIADICS_MSVC
#  define LOGGER(...) BOOST_PP_OVERLOAD(LOGGER_,__VA_ARGS__)(__VA_ARGS__)
#else
#  define LOGGER(...) BOOST_PP_CAT(BOOST_PP_OVERLOAD(LOGGER_,__VA_ARGS__)(__VA_ARGS__),BOOST_PP_EMPTY())
#endif

#define LOGGER_NO_TRACE(logger) solution::shared::Logger logger(FUNCTION, false)

#define LOGGER_WRITE(logger, message) logger.write(solution::shared::Logger::Severity::empty, message);

#if defined(_DEBUG)
#  define LOGGER_WRITE_DEBUG(logger, message) logger.write(solution::shared::Logger::Severity::debug, message);
#else
#  define LOGGER_WRITE_DEBUG(logger, message) ;
#endif

#define LOGGER_WRITE_TRACE(logger, message) logger.write(solution::shared::Logger::Severity::trace, message);
#define LOGGER_WRITE_ERROR(logger, message) logger.write(solution::shared::Logger::Severity::error, message);
#define LOGGER_WRITE_FATAL(logger, message) logger.write(solution::shared::Logger::Severity::fatal, message);