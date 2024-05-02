#if (!defined(FUNCTION))
#  if (defined(_MSC_VER) || defined(__GNUC__))
#    define FUNCTION __FUNCTION__
#  else
#    define FUNCTION __func__
#  endif
#else
#  error "invalid macro definition"
#endif

#include <cstdlib>
#include <exception>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>

using namespace std::literals;

#include <boost/date_time/posix_time/posix_time.hpp> // note: support
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
#include <boost/make_shared.hpp> // note: support
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp> // note: support

//  ================================================================================================

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

	static void initialize()
	{
		for (const auto & [type, attribute] : attributes)
		{
			if (type != Attribute::severity && !logger.add_attribute(attribute.first, attribute.second).second)
			{
				throw std::logic_error("invalid attribute [" + attribute.first + "]");
			}
		}

		boost::log::core::get()->add_sink(make_fout_sink());
	}

	static boost::shared_ptr < sink_t > make_fout_sink()
	{
		const auto day = boost::posix_time::hours(24);

		const auto fout_sink_ptr = boost::make_shared < sink_t > (

			boost::log::keywords::file_name = "%y.%m.%d.%H.%M.%S.log",
			boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_interval(day),
			boost::log::keywords::rotation_size = 32 * 1024 * 1024,
			boost::log::keywords::max_size      = 64 * 1024 * 1024);

		fout_sink_ptr->locked_backend()->set_file_collector(boost::log::sinks::file::make_collector(
			
			boost::log::keywords::target = "loggers",
			boost::log::keywords::max_size       = 128 * 1024 * 1024,
			boost::log::keywords::min_free_space = 128 * 1024 * 1024));

		fout_sink_ptr->locked_backend()->auto_flush(true);

		fout_sink_ptr->set_formatter(&Logger::fout_formatter);

		fout_sink_ptr->set_filter([](boost::log::attribute_value_set) noexcept { return true; });

		return fout_sink_ptr;
	}

	static void fout_formatter(const boost::log::record_view & record_view, boost::log::formatting_ostream & stream)
	{
		const auto & attribute_value_set = record_view.attribute_values();

		stream << std::dec << std::setw(8) << std::right << std::setfill('0') <<
			boost::log::extract_or_throw < std::size_t > (attribute_value_set[
				attributes.at(Attribute::line).first]) << std::setfill(' ') << separator;

		auto date_time_formatter =
			boost::log::expressions::stream <<
			boost::log::expressions::format_date_time < boost::posix_time::ptime > (
				attributes.at(Attribute::time).first, "%Y %B %e %H:%M:%S.%f");

		date_time_formatter(record_view, stream);

		stream << separator;

		stream << boost::log::extract_or_throw < boost::log::attributes::current_process_id::value_type > (
			attribute_value_set[attributes.at(Attribute::process).first]) << separator;

		stream << boost::log::extract_or_throw < boost::log::attributes::current_thread_id::value_type > (
			attribute_value_set[attributes.at(Attribute::thread).first]) << separator;

		stream << severities.at(boost::log::extract_or_throw < Severity > (
			attribute_value_set[attributes.at(Attribute::severity).first])) << separator;

		stream << record_view[boost::log::expressions::message];
	}

public:

	[[nodiscard]] const char * scope() const noexcept { return m_scope; }

	[[nodiscard]] static std::string_view severity_as_string(Severity severity)
	{
		return severities.at(severity);
	}

public:

	void write(Severity severity, const std::string & message) const noexcept
	{
		try
		{
			if (auto record = logger.open_record(boost::log::keywords::severity = severity); record)
			{
				boost::log::record_ostream(record) << m_scope << separator << message;

				logger.push_record(std::move(record));
			}
			else throw std::runtime_error("invalid record");
		}
		catch (const std::exception & exception)
		{
			catch_handler(FUNCTION, exception.what());
		}
	}

private:

	static void catch_handler(std::string_view scope, std::string_view message) noexcept
	{
		try { std::cerr << scope << " : " << message << '\n'; } catch (...) {}
	}

private:

	static constexpr auto separator = " : ";

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

	const char * const m_scope;

	const bool m_has_trace;

}; // class Logger : private boost::noncopyable

template < typename E > inline void catch_handler(const Logger & logger, const std::exception & exception)
{
	static_assert(std::is_base_of_v < std::exception, E > , "invalid exception type");

	logger.write(Logger::Severity::error, exception.what());

	throw E(logger.scope() + " exception"s);
}

//  ================================================================================================

#define LOGGER(logger) const Logger logger(FUNCTION)

#define LOGGER_WRITE_DEBUG(logger, message) logger.write(Logger::Severity::debug, message);
#define LOGGER_WRITE_TRACE(logger, message) logger.write(Logger::Severity::trace, message);
#define LOGGER_WRITE_ERROR(logger, message) logger.write(Logger::Severity::error, message);
#define LOGGER_WRITE_FATAL(logger, message) logger.write(Logger::Severity::fatal, message);

//  ================================================================================================

void h()
{
	LOGGER(logger);

	try
	{
		LOGGER_WRITE_ERROR(logger, "message"); throw std::logic_error("error");
	}
	catch (const std::exception & exception)
	{
		catch_handler < std::runtime_error > (logger, exception);
	}
}

//  ================================================================================================

void g() { LOGGER(logger); h(); }
void f() { LOGGER(logger); g(); }

//  ================================================================================================

int main()
{
	LOGGER(logger);

	try
	{
		f();

		return EXIT_SUCCESS;
	}
	catch (const std::exception & exception)
	{
		LOGGER_WRITE_FATAL(logger, exception.what());

		return EXIT_FAILURE;
	}
	catch (...)
	{
		LOGGER_WRITE_FATAL(logger, "unknown exception");

		return EXIT_FAILURE;
	}
}