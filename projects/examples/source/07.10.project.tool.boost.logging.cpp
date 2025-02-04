#include <exception>
#include <format>
#include <mutex>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/common.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/make_shared.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

//////////////////////////////////////////////////////////////////////////////////////////////////

class Logger : private boost::noncopyable
{
public:

	enum class Severity : std::uint8_t
	{
		debug, trace, error, fatal
	};

//  ----------------------------------------------------------------------------------------------

	Logger(const char * scope, bool has_trace) : m_scope(scope), m_has_trace(has_trace)
	{
		std::call_once(s_status, initialize);

		if (m_has_trace) 
		{
			write(Severity::trace, "execution ... ");
		}
	}

   ~Logger()
	{
		if (m_has_trace) 
		{
			write(Severity::trace, "execution complete");
		}
	}

//  ----------------------------------------------------------------------------------------------

	void write(Severity severity, const std::string & string) const
	{
		if (auto record = s_logger.open_record(boost::log::keywords::severity = severity); record)
		{
			boost::log::record_ostream(record) << m_scope << " : " << string;

			s_logger.push_record(std::move(record));
		}
		else 
		{
			throw std::runtime_error("invalid record");
		}
	}

private:

	using sink_t = boost::log::sinks::synchronous_sink < boost::log::sinks::text_file_backend > ;

//  ----------------------------------------------------------------------------------------------

	static void initialize()
	{
        std::vector < std::pair < std::string, boost::log::attribute > > attributes = 
        {
            { "line",    boost::log::attributes::counter < std::size_t > () },

            { "time",    boost::log::attributes::utc_clock() },

            { "process", boost::log::attributes::current_process_id() },

            { "thread",  boost::log::attributes::current_thread_id () }
        };

		for (const auto & [name, attribute] : attributes)
		{
			if (!s_logger.add_attribute(name, attribute).second)
			{
				throw std::runtime_error("invalid attribute");
			}
		}

		boost::log::core::get()->add_sink(make_sink());
	}

//  ----------------------------------------------------------------------------------------------

	static auto make_sink() -> boost::shared_ptr < sink_t >
	{
		auto rotation = boost::log::sinks::file::rotation_at_time_interval
		(
			boost::posix_time::hours(24)
		);

		auto sink = boost::make_shared < sink_t > 
		(
			boost::log::keywords::file_name = "%y.%m.%d.%H.%M.%S.log",

			boost::log::keywords::time_based_rotation = rotation,

			boost::log::keywords::rotation_size = 8 * 1'024 * 1'024
		);

		sink->locked_backend()->auto_flush(true);

		sink->locked_backend()->set_file_collector
		(
			boost::log::sinks::file::make_collector(boost::log::keywords::target = "loggers")
		);		

		sink->set_formatter(&format);

		sink->set_filter([](boost::log::attribute_value_set){ return true; });

		return sink;
	}

//  ----------------------------------------------------------------------------------------------

	static void format(boost::log::record_view record, boost::log::formatting_ostream & stream)
	{
		const auto & attributes = record.attribute_values();

		stream << std::format
		(
			"{:0>8}", boost::log::extract_or_throw < std::size_t > (attributes["line"])
		);

		auto timestamp = boost::log::expressions::format_date_time < boost::posix_time::ptime > 
		(
			"time", "%Y %B %e %H:%M:%S.%f"
		);

		(boost::log::expressions::stream << " | " << timestamp)(record, stream);

		using pid_t = boost::log::attributes::current_process_id::value_type;

		using tid_t = boost::log::attributes::current_thread_id ::value_type;

		stream << " | " << boost::log::extract_or_throw < pid_t > (attributes["process"]);
		
		stream << " | " << boost::log::extract_or_throw < tid_t > (attributes["thread" ]);

        switch (boost::log::extract_or_throw < Severity > (attributes["Severity"]))
        {
            case Severity::debug: { stream << " | debug"; break; }

            case Severity::trace: { stream << " | trace"; break; }

            case Severity::error: { stream << " | error"; break; }

            case Severity::fatal: { stream << " | fatal"; break; }

            default:
            {
                throw std::runtime_error("invalid severity"); 
            }
        }

		stream << " | " << record[boost::log::expressions::message];
	}

//  ----------------------------------------------------------------------------------------------

	const char * m_scope = nullptr; bool m_has_trace = true;

//  ----------------------------------------------------------------------------------------------

    static inline std::once_flag s_status;

    static inline boost::log::sources::severity_logger_mt < Severity > s_logger;
};

//////////////////////////////////////////////////////////////////////////////////////////////////

#define LOGGER(logger) Logger logger(__func__, false)

//////////////////////////////////////////////////////////////////////////////////////////////////

#define LOGGER_WRITE_DEBUG(logger, string) logger.write(Logger::Severity::debug, string);

#define LOGGER_WRITE_TRACE(logger, string) logger.write(Logger::Severity::trace, string);

#define LOGGER_WRITE_ERROR(logger, string) logger.write(Logger::Severity::error, string);

#define LOGGER_WRITE_FATAL(logger, string) logger.write(Logger::Severity::fatal, string);

//////////////////////////////////////////////////////////////////////////////////////////////////

void test_v1()
{
	LOGGER(logger);
		
	throw std::runtime_error("error");
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void test_v2() { LOGGER(logger); test_v1(); }

void test_v3() { LOGGER(logger); test_v2(); }

//////////////////////////////////////////////////////////////////////////////////////////////////

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