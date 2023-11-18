#include "custom_logger.hpp"

namespace solution
{
	namespace shared
	{
		void Logger::initialize()
		{
			try
			{
				add_attributes(); 
				
				add_sinks();

				status = true;
			}
			catch (const std::exception & exception)
			{
				uninitialize();

				catch_handler < logger_exception > (FUNCTION, exception);
			}
		}

		void Logger::add_attributes()
		{
			try
			{
				for (const auto & attribute : attributes)
				{
					if (attribute.first != Attribute_Index::severity)
					{
						if (!logger.add_attribute(attribute.second.first, *(attribute.second.second)).second)
						{
							throw logger_exception("invalid attribute [" + attribute.second.first + "]");
						}
					}
				}
			}
			catch (const std::exception & exception)
			{
				catch_handler < logger_exception > (FUNCTION, exception);
			}
		}

		void Logger::add_sinks()
		{
			try
			{
				boost::log::core::get()->add_sink(make_fout_sink());
			}
			catch (const std::exception & exception)
			{
				catch_handler < logger_exception > (FUNCTION, exception);
			}
		}

		void Logger::uninitialize()
		{
			try
			{
				remove_sinks(); 
				
				remove_attributes();

				status = false;
			}
			catch (const std::exception & exception)
			{
				catch_handler < logger_exception > (FUNCTION, exception);
			}
		}

		void Logger::remove_attributes()
		{
			try
			{
				logger.remove_all_attributes();
			}
			catch (const std::exception & exception)
			{
				catch_handler < logger_exception > (FUNCTION, exception);
			}
		}

		void Logger::remove_sinks()
		{
			try
			{
				boost::log::core::get()->remove_all_sinks();
			}
			catch (const std::exception & exception)
			{
				catch_handler < logger_exception > (FUNCTION, exception);
			}
		}

		boost::shared_ptr < Logger::sink_t > Logger::make_fout_sink()
		{
			try
			{
				auto fout_sink_ptr =
					boost::make_shared < sink_t > (
						boost::log::keywords::file_name = "%y.%m.%d.%H.%M.%S.log",
						boost::log::keywords::time_based_rotation =
							boost::log::sinks::file::rotation_at_time_interval(boost::posix_time::hours(24L)),
						boost::log::keywords::rotation_size = 32 * 1024 * 1024,
						boost::log::keywords::max_size      = 64 * 1024 * 1024);

				fout_sink_ptr->locked_backend()->set_file_collector(
					boost::log::sinks::file::make_collector(
						boost::log::keywords::target = "logger",
						boost::log::keywords::max_size       = 128 * 1024 * 1024,
						boost::log::keywords::min_free_space = 128 * 1024 * 1024));

				fout_sink_ptr->locked_backend()->auto_flush(true);

				fout_sink_ptr->set_formatter(&Logger::fout_formatter);
				fout_sink_ptr->set_filter   (&Logger::fout_filter);

				return fout_sink_ptr;
			}
			catch (const std::exception & exception)
			{
				catch_handler < logger_exception > (FUNCTION, exception);
			}
		}

		void Logger::fout_formatter(const boost::log::record_view & record_view, boost::log::formatting_ostream & stream)
		{
			try
			{
				const boost::log::attribute_value_set & attribute_value_set = record_view.attribute_values();

				stream << "0x" << std::dec << std::setw(8) << std::setfill('0');

				stream << boost::log::extract_or_throw < std::size_t > (
					attribute_value_set[attributes.at(Attribute_Index::line).first]);

				stream << std::setfill(' ') << separator;

				auto date_time_formatter =
					boost::log::expressions::stream <<
					boost::log::expressions::format_date_time < boost::posix_time::ptime > (
						attributes.at(Attribute_Index::time).first, "%Y %B %e %H:%M:%S.%f");

				date_time_formatter(record_view, stream);

				stream << separator;

				stream << severities.at(boost::log::extract_or_throw < Severity > (
					attribute_value_set[attributes.at(Attribute_Index::severity).first])) << separator;

				stream << boost::log::extract_or_throw < boost::log::attributes::current_process_id::value_type > (
					attribute_value_set[attributes.at(Attribute_Index::process).first]) << separator;

				stream << boost::log::extract_or_throw < boost::log::attributes::current_thread_id::value_type > (
					attribute_value_set[attributes.at(Attribute_Index::thread).first]) << separator;

				stream << record_view[boost::log::expressions::message];
			}
			catch (const std::exception & exception)
			{
				catch_handler < logger_exception > (FUNCTION, exception);
			}
		}

		bool Logger::fout_filter([[maybe_unused]] const boost::log::attribute_value_set & attribute_value_set)
		{
			return true;
		}

		void Logger::write(Severity severity, const std::string & message) const noexcept
		{
			try
			{
				if (!status)
				{
					throw logger_exception("logger is not initialized");
				}

				auto record = logger.open_record(boost::log::keywords::severity = severity);

				if (record)
				{
					boost::log::record_ostream stream(record);

					stream << m_scope << separator << message;

					logger.push_record(std::move(record));
				}
				else
				{
					throw logger_exception("record open error");
				}
			}
			catch (const std::exception & exception)
			{
				catch_handler(FUNCTION, exception);
			}
		}

		const Logger::attributes_container_t Logger::attributes =
		{
			{ Logger::Attribute_Index::line, std::make_pair("line",
				std::make_shared < boost::log::attributes::counter < std::size_t > > ()) },

			{ Logger::Attribute_Index::time, std::make_pair("time",
				std::make_shared < boost::log::attributes::utc_clock > ()) },

			{ Logger::Attribute_Index::severity, std::make_pair(boost::log::aux::default_attribute_names::severity().string(),
				std::shared_ptr < boost::log::attribute > (nullptr)) },

			{ Logger::Attribute_Index::process, std::make_pair("process",
				std::make_shared < boost::log::attributes::current_process_id > ()) },

			{ Logger::Attribute_Index::thread, std::make_pair("thread",
				std::make_shared < boost::log::attributes::current_thread_id > ()) }
		};

		const Logger::severities_container_t Logger::severities =
		{
			{ Logger::Severity::empty, "empty" },
			{ Logger::Severity::debug, "debug" },
			{ Logger::Severity::trace, "trace" },
			{ Logger::Severity::error, "error" },
			{ Logger::Severity::fatal, "fatal" }
		};

		std::once_flag Logger::is_initialized_once;

		Logger::logger_t Logger::logger;
		Logger::status_t Logger::status;

		void catch_handler(Logger & logger, const std::exception & exception) noexcept
		{
			logger.write(Logger::Severity::error, exception.what());
		}

	} // namespace shared

} // namespace solution 