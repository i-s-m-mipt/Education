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

namespace solution
{
	namespace shared
	{
		using namespace std::literals;

		class logger_exception : public std::exception 
		{
		public:

			explicit logger_exception(const std::string & message) noexcept : std::exception(message.c_str()) {}

		}; // class logger_exception : public std::exception 

		class Logger : private boost::noncopyable
		{			
		private:

			enum class Attribute_Index
			{
				line,
				time,
				severity,
				thread,
				process,

			}; // enum class Attribute_Index

		private:

			using attributes_container_t = std::unordered_map < Attribute_Index,
				std::pair < std::string, std::shared_ptr < boost::log::attribute > > > ;

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

			using severities_container_t = std::unordered_map < Severity, std::string_view > ;

		private:

			using sink_t = boost::log::sinks::synchronous_sink < boost::log::sinks::text_file_backend > ;

		private:

			using logger_t = boost::log::sources::severity_logger_mt < Severity > ;

			using status_t = bool;

		public:

			explicit Logger(std::string scope, bool has_trace = true) : m_scope(std::move(scope)), m_has_trace(has_trace)
			{
				try
				{
					std::call_once(is_initialized_once, &Logger::initialize);

					if (m_has_trace)
					{
						write(Severity::trace, "EXECUTION ... ");
					}
				}
				catch (const std::exception & exception)
				{
					catch_handler(FUNCTION, exception);
				}
			}

			~Logger() noexcept
			{
				try
				{
					if (m_has_trace)
					{
						write(Severity::trace, "EXECUTION COMPLETE");
					}
				}
				catch (...)
				{
					std::abort();
				}
			}

		private:

			static void initialize();

		private:

			static void add_attributes();

			static void add_sinks();

		private:

			static void uninitialize();

		private:

			static void remove_attributes();

			static void remove_sinks();

		private:

			static boost::shared_ptr < sink_t > make_fout_sink();

		private:

			static void fout_formatter(const boost::log::record_view & record_view, boost::log::formatting_ostream & stream);

			static bool fout_filter([[maybe_unused]] const boost::log::attribute_value_set & attribute_value_set);

		public:

			[[nodiscard]] const auto & scope() const noexcept
			{
				return m_scope;
			}

		public:

			void write(Severity severity, const std::string & message) const noexcept;

		private:

			static void catch_handler(const std::string & scope, const std::exception & exception) noexcept
			{
				try
				{
					std::cerr << scope << separator << exception.what() << '\n';
				}
				catch (...)
				{
					std::abort();
				}
			}

			template < typename E >
			static void	catch_handler(const std::string & scope, const std::exception & exception)
			{
				static_assert(std::is_same_v < logger_exception, E > , "invalid exception type");

				try
				{
					std::cerr << scope << separator << exception.what() << '\n';
				}
				catch (...)
				{
					std::abort();
				}

				throw E(scope + " exception");
			}

		private:

			static inline const auto separator = " : "s;

		private:

			static const attributes_container_t attributes;
			static const severities_container_t severities;

		private:

			static std::once_flag is_initialized_once;

			static logger_t logger;
			static status_t status;

		private:

			const std::string m_scope;

		private:

			bool m_has_trace;

		}; // class Logger : private boost::noncopyable

		template < typename E >
		void catch_handler(Logger & logger, const std::exception & exception)
		{
			static_assert(std::is_base_of_v < std::exception, E >, "invalid exception type");

			logger.write(Logger::Severity::error, exception.what());

			throw E(logger.scope() + " exception");
		}

		template < typename E >
		void catch_handler(Logger & logger)
		{
			static_assert(std::is_base_of_v < std::exception, E >, "invalid exception type");

			logger.write(Logger::Severity::error, "unknown exception");

			throw E(logger.scope() + " exception");
		}

		void catch_handler(Logger & logger, const std::exception & exception) noexcept;

	} // namespace shared

} // namespace solution 

#define LOGGER_2(logger, has_trace) solution::shared::Logger logger(FUNCTION, has_trace)

#define LOGGER_1(logger) LOGGER_2(logger, true)

#if !BOOST_PP_VARIADICS_MSVC
#  define LOGGER(...) BOOST_PP_OVERLOAD(LOGGER_,__VA_ARGS__)(__VA_ARGS__)
#else
#  define LOGGER(...) BOOST_PP_CAT(BOOST_PP_OVERLOAD(LOGGER_,__VA_ARGS__)(__VA_ARGS__),BOOST_PP_EMPTY())
#endif

#define LOGGER_WRITE(logger, message) logger.write(solution::shared::Logger::Severity::empty, message);

#if defined(_DEBUG)
#  define LOGGER_WRITE_DEBUG(logger, message) logger.write(solution::shared::Logger::Severity::debug, message);
#else
#  define LOGGER_WRITE_DEBUG(logger, message) ;
#endif

#define LOGGER_WRITE_TRACE(logger, message) logger.write(solution::shared::Logger::Severity::trace, message);
#define LOGGER_WRITE_ERROR(logger, message) logger.write(solution::shared::Logger::Severity::error, message);
#define LOGGER_WRITE_FATAL(logger, message) logger.write(solution::shared::Logger::Severity::fatal, message);