#include "custom_logger.hpp"

namespace solution::shared
{
	void Logger::initialize()
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

	boost::shared_ptr < Logger::sink_t > Logger::make_fout_sink()
	{
		const auto day = boost::posix_time::hours(24);

		auto fout_sink_ptr = boost::make_shared < sink_t > (
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

		fout_sink_ptr->set_filter([](boost::log::attribute_value_set){ return true; });

		return fout_sink_ptr;
	}

	void Logger::fout_formatter(const boost::log::record_view & record_view, boost::log::formatting_ostream & stream)
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

	void Logger::write(Severity severity, const std::string & message) const noexcept
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

} // namespace solution::shared 