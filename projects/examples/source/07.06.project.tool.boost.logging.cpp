#include <cstdint>
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
#include <boost/shared_ptr.hpp>

//  ================================================================================================

class Logger : private boost::noncopyable
{
private:

	enum class Attribute : std::uint8_t
	{
		line,
		time,
		thread,
		process,
	};

	using attribute_pair_t = std::pair < std::string, boost::log::attribute > ;

public:

	enum class Severity : std::uint8_t
	{
		debug,
		trace,
		error,
		fatal,
	};

private:

	using sink_t = boost::log::sinks::synchronous_sink < boost::log::sinks::text_file_backend > ;

public:

	explicit Logger(const char * scope, bool has_trace) : m_scope(scope), m_has_trace(has_trace)
	{
		std::call_once(s_status, Logger::initialize);

		if (m_has_trace) 
		{
			write(Severity::trace, "EXECUTION ... ");
		}
	}

   ~Logger()
	{
		if (m_has_trace) 
		{
			write(Severity::trace, "EXECUTION COMPLETE");
		}
	}

private:

	static void initialize()
	{
		for (const auto & [type, attribute] : s_attributes)
		{
			if (!s_logger.add_attribute(attribute.first, attribute.second).second)
			{
				throw std::runtime_error("invalid attribute");
			}
		}

		boost::log::core::get()->add_sink(make_sink());
	}

	static boost::shared_ptr < sink_t > make_sink()
	{
		auto rotation = boost::log::sinks::file::rotation_at_time_interval
		(
			boost::posix_time::hours(24)
		);

		auto fout_sink = boost::make_shared < sink_t > 
		(
			boost::log::keywords::file_name           = "%y.%m.%d.%H.%M.%S.log",
			boost::log::keywords::time_based_rotation = rotation,
			boost::log::keywords::rotation_size       = 32 * 1024 * 1024,
			boost::log::keywords::max_size            = 64 * 1024 * 1024
		);

		fout_sink->locked_backend()->set_file_collector
		(
			boost::log::sinks::file::make_collector
			(			
				boost::log::keywords::target         = "loggers",
				boost::log::keywords::max_size       = 128 * 1024 * 1024,
				boost::log::keywords::min_free_space = 128 * 1024 * 1024
			)
		);

		fout_sink->locked_backend()->auto_flush(true);

		fout_sink->set_formatter(&Logger::format);

		fout_sink->set_filter
		(
			[](boost::log::attribute_value_set){ return true; }
		);

		return fout_sink;
	}

	static void format
	(
		const boost::log::record_view & record_view, boost::log::formatting_ostream & stream
	)
	{
		const auto & attribute_value_set = record_view.attribute_values();

		const auto & line = attribute_value_set[s_attributes.at(Attribute::line).first];

		stream << std::setw(8) << std::setfill('0') << std::right;
		
		stream << std::dec << boost::log::extract_or_throw < std::size_t > (line);
		
		stream << std::setfill(' ') << " | ";

		auto date_time_expression = boost::log::expressions::format_date_time 
		< 
			boost::posix_time::ptime 
		> 
		(
			s_attributes.at(Attribute::time).first, "%Y %B %e %H:%M:%S.%f"
		);

		(boost::log::expressions::stream << date_time_expression)(record_view, stream);

		stream << " | ";

		using pid_t = boost::log::attributes::current_process_id::value_type;
		using tid_t = boost::log::attributes::current_thread_id ::value_type;

		const auto & pid = attribute_value_set[s_attributes.at(Attribute::process).first];
		const auto & tid = attribute_value_set[s_attributes.at(Attribute::thread ).first];

		stream << boost::log::extract_or_throw < pid_t > (pid) << " | ";
		stream << boost::log::extract_or_throw < tid_t > (tid) << " | ";

		const auto & severity = attribute_value_set["Severity"];

		stream << s_severities.at(boost::log::extract_or_throw < Severity > (severity)) << " | ";

		stream << record_view[boost::log::expressions::message];
	}

public:

	auto scope() const 
	{ 
		return m_scope; 
	}

//  ----------------------------------------------------------------

	void write(Severity severity, const std::string & message) const
	{
		auto record = s_logger.open_record(boost::log::keywords::severity = severity);

		if (record)
		{
			boost::log::record_ostream(record) << m_scope << " : " << message;

			s_logger.push_record(std::move(record));
		}
		else 
		{
			throw std::runtime_error("invalid record");
		}
	}

private:

	static inline const std::unordered_map < Attribute, attribute_pair_t > s_attributes
	{
		{ Attribute::line   , { "line"   , boost::log::attributes::counter < std::size_t > () } },
		{ Attribute::time   , { "time"   , boost::log::attributes::utc_clock               () } },
		{ Attribute::process, { "process", boost::log::attributes::current_process_id      () } },
		{ Attribute::thread , { "thread" , boost::log::attributes::current_thread_id       () } }
	};

	static inline const std::unordered_map < Severity, std::string_view > s_severities
	{
		{ Logger::Severity::debug, "debug" },
		{ Logger::Severity::trace, "trace" },
		{ Logger::Severity::error, "error" },
		{ Logger::Severity::fatal, "fatal" }
	};

//  --------------------------------------

	static inline std::once_flag s_status;

	static inline boost::log::sources::severity_logger_mt < Severity > s_logger;

//  ----------------------------------------------------------------------------

	const char * m_scope = nullptr; bool m_has_trace = true;
};

//  ================================================================================================

#define LOGGER(logger) Logger logger(__func__, true)

#define LOGGER_WRITE_DEBUG(logger, message) logger.write(Logger::Severity::debug, message);
#define LOGGER_WRITE_TRACE(logger, message) logger.write(Logger::Severity::trace, message);
#define LOGGER_WRITE_ERROR(logger, message) logger.write(Logger::Severity::error, message);
#define LOGGER_WRITE_FATAL(logger, message) logger.write(Logger::Severity::fatal, message);

//  ================================================================================================

void test_v1()
{
	LOGGER(logger);
		
	throw std::runtime_error("error");
}

//  ================================================================================================

void test_v2() { LOGGER(logger); test_v1(); }
void test_v3() { LOGGER(logger); test_v2(); }

//  ================================================================================================

int main()
{
	LOGGER(logger);

	try
	{
		test_v3();

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