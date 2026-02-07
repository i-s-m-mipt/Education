///////////////////////////////////////////////////////////////////////////////////////////

// chapter : Debugging and Profiling

///////////////////////////////////////////////////////////////////////////////////////////

// section : Software Analysis Tools

///////////////////////////////////////////////////////////////////////////////////////////

// content : Library Google.Log
//
// content : Operator ""h

///////////////////////////////////////////////////////////////////////////////////////////

#include <chrono>
#include <cstdint>
#include <exception>
#include <format>
#include <mutex>
#include <ostream>
#include <source_location>
#include <stdexcept>
#include <string>

///////////////////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

///////////////////////////////////////////////////////////////////////////////////////////

#include <boost/noncopyable.hpp>

///////////////////////////////////////////////////////////////////////////////////////////

#include <glog/logging.h>

///////////////////////////////////////////////////////////////////////////////////////////

class Logger : private boost::noncopyable
{
public :

	enum class Severity : std::uint8_t
	{
		trace, debug, error, fatal
	};

//  -------------------------------------------------------------------------------------

	Logger(char const * scope, bool has_trace) : m_scope(scope), m_has_trace(has_trace)
	{
		std::call_once(s_flag, initialize);

		if (m_has_trace) 
		{
			put(Severity::trace, "execution ... ");
		}
	}

//  -------------------------------------------------------------------------------------

   ~Logger()
	{
		if (m_has_trace) 
		{
			put(Severity::trace, "execution complete");
		}
	}

//  -------------------------------------------------------------------------------------

	void put(Severity severity, std::string const & string) const
	{
		switch (severity)
        {
            case Severity::trace : { LOG(INFO   ) << m_scope << " : " << string; break; }

            case Severity::debug : { LOG(WARNING) << m_scope << " : " << string; break; }

            case Severity::error : { LOG(ERROR  ) << m_scope << " : " << string; break; }

            case Severity::fatal : { LOG(FATAL  ) << m_scope << " : " << string; break; }
        }
	}

private :

	static void initialize()
	{
        FLAGS_log_dir = "loggers";

        FLAGS_log_file_header = false;

        google::InitGoogleLogging("07.20");

        google::EnableLogCleaner(24h);

		google::InstallPrefixFormatter(&format);
	}

//  -------------------------------------------------------------------------------------

	static void format(std::ostream & stream, google::LogMessage const & message, void *)
	{
		stream << std::format("{:0>8}", s_line++) << " | ";

        stream << std::format("{:%Y %B %d %H:%M:%S %Z}", message.time().when()) << " | ";

        stream << message.thread_id() << " | ";

        switch (message.severity())
        {
            case google::LogSeverity::INFO    : { stream << "trace |"; break; }

            case google::LogSeverity::WARNING : { stream << "debug |"; break; }

            case google::LogSeverity::ERROR   : { stream << "error |"; break; }

            case google::LogSeverity::FATAL   : { stream << "fatal |"; break; }
        }
	}

//  -------------------------------------------------------------------------------------

	char const * m_scope = nullptr;

	bool m_has_trace = false;

//  -------------------------------------------------------------------------------------

    static inline std::once_flag s_flag;

    static inline auto s_line = 0uz;
};

///////////////////////////////////////////////////////////////////////////////////////////

#define LOGGER(logger) Logger logger(std::source_location::current().function_name(), true)

///////////////////////////////////////////////////////////////////////////////////////////

void test_v1()
{
	LOGGER(logger);

	throw std::runtime_error("error");
}

///////////////////////////////////////////////////////////////////////////////////////////

void test_v2() { LOGGER(logger); test_v1(); }

void test_v3() { LOGGER(logger); test_v2(); }

///////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	LOGGER(logger);

//  -------------------------------------------------------------

	try
	{
		test_v3();
	}
	catch (std::exception const & exception)
	{
		logger.put(Logger::Severity::fatal, exception.what());
	}
	catch (...)
	{
		logger.put(Logger::Severity::fatal, "unknown exception");
	}
}

///////////////////////////////////////////////////////////////////////////////////////////