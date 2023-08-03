#include <chrono>
#include <cstdlib>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include <boost/asio.hpp>

namespace solution
{
	class Controller
	{
	public:

		using protocol_t = boost::asio::ip::tcp;

		using endpoint_t = protocol_t::endpoint;

		using ip_address_t = boost::asio::ip::address;

		using socket_t = protocol_t::socket;

		using sockets_container_t = std::vector < socket_t >;

	private:

		struct Request
		{
			std::uint8_t  control_sum      = 0x00;
			std::uint8_t  protocol_version = 0x03;
			std::uint8_t  command_type     = 0x00;
			std::uint8_t  command_id       = 0x00;
			std::uint16_t data_length      = 0x00;
		};

		struct Password
		{
			std::uint8_t  control_sum      = 0x00;
			std::uint8_t  protocol_version = 0x03;
			std::uint8_t  command_type     = 0x00;
			std::uint8_t  command_id       = 0x00;
			std::uint16_t data_length      = 0x08;

			std::uint8_t  data[8] = {};
		};

		struct Response
		{
			std::uint8_t  control_sum      = 0x00;
			std::uint8_t  protocol_version = 0x03;
			std::uint8_t  command_type     = 0x01;
			std::uint8_t  command_id       = 0x00;
			std::uint16_t data_length      = 0x07;

			std::uint8_t  data[7] = {};
		};

		struct Package
		{
			std::uint8_t  control_sum      = 0x00;
			std::uint8_t  protocol_version = 0x03;
			std::uint8_t  command_type     = 0x02;
			std::uint8_t  command_id       = 0x00;
			std::uint16_t data_length      = 0x04;

			std::uint8_t  data[4] = {};
		};

		struct Command
		{
			std::uint32_t reserve : 3;
			std::uint32_t action  : 1;
			std::uint32_t command : 6;
			std::uint32_t data    : 22;
		};

		struct Status
		{
			std::uint8_t  control_sum      = 0x00;
			std::uint8_t  protocol_version = 0x03;
			std::uint8_t  command_type     = 0x02;
			std::uint8_t  command_id       = 0x00;
			std::uint16_t data_length      = 0x07;

			std::uint8_t  data[7] = {};
		};

	public:

		explicit Controller(const std::initializer_list <
			std::pair < std::string, unsigned int > >& endpoints)
		{
			m_sockets.reserve(std::size(endpoints));

			for (const auto& [ip_address, port] : endpoints)
			{
				endpoint_t endpoint(ip_address_t::from_string(ip_address), port);

				socket_t socket(m_io_service, endpoint.protocol());

				socket.connect(endpoint);

				std::cout << "Socket on [" << ip_address << ":" << port << "] " <<
					"successfully created" << std::endl;

				receive(socket, sizeof(Request));

				Password password;

				password.data[0] = 0xEF;
				password.data[1] = 0xCD;
				password.data[2] = 0xAB;
				password.data[3] = 0x89;
				password.data[4] = 0x67;
				password.data[5] = 0x45;
				password.data[6] = 0x23;
				password.data[7] = 0x01;

				send(socket, password);

				if (receive(socket, sizeof(Response) - 1) == ok_access)
				{
					std::cout << "Controller on [" << ip_address << ":" <<
						port << "] " << "ready to work" << std::endl;
				}
				else
				{
					std::cout << "Controller on [" << ip_address << ":" <<
						port << "] " << "failed to login" << std::endl;
				}

				m_sockets.push_back(std::move(socket));
			}
		}

		~Controller() noexcept = default;

	public:

		void move(char direction, std::uint32_t speed = 0U)
		{
			Command command_1;
			Command command_2;

			command_1.reserve = 0;
			command_2.reserve = 0;

			command_1.action = 0;
			command_2.action = 0;

			command_1.data = std::min(std::max(speed, min_speed), max_speed);
			command_2.data = std::min(std::max(speed, min_speed), max_speed);

			switch (direction)
			{
			case 'f': case 'F':
			{
				command_1.command = 0x0E;
				command_2.command = 0x0F;

				break;
			}
			case 'b': case 'B':
			{
				command_1.command = 0x0F;
				command_2.command = 0x0E;

				break;
			}
			case 's': case 'S':
			{
				command_1.command = 0x0E;
				command_2.command = 0x0F;

				command_1.data = 0;
				command_2.data = 0;

				break;
			}
			default:
			{
				return;
			}
			}

			Package package_1;
			Package package_2;

			memcpy(package_1.data, &command_1, sizeof(command_1));
			memcpy(package_2.data, &command_2, sizeof(command_2));

			send(m_sockets[0], package_1);

			receive(m_sockets[0], sizeof(Status) - 1);

			send(m_sockets[1], package_2);

			receive(m_sockets[1], sizeof(Status) - 1);
		}

		void stop()
		{
			Command command_1;
			Command command_2;

			command_1.reserve = 0;
			command_2.reserve = 0;

			command_1.action = 0;
			command_2.action = 0;

			command_1.command = 0x22;
			command_2.command = 0x22;

			command_1.data = 0;
			command_2.data = 0;

			Package package_1;
			Package package_2;

			memcpy(package_1.data, &command_1, sizeof(command_1));
			memcpy(package_2.data, &command_2, sizeof(command_2));

			send(m_sockets[0], package_1);

			receive(m_sockets[0], sizeof(Status) - 1);

			send(m_sockets[1], package_2);

			receive(m_sockets[1], sizeof(Status) - 1);
		}

		void set_acceleration(std::uint32_t acceleration = 0U)
		{
			Command command_1;
			Command command_2;

			command_1.reserve = 0;
			command_2.reserve = 0;

			command_1.action = 0;
			command_2.action = 0;

			command_1.command = 0x07;
			command_2.command = 0x07;

			command_1.data = std::min(std::max(acceleration, min_acceleration), max_acceleration);
			command_2.data = std::min(std::max(acceleration, min_acceleration), max_acceleration);

			Package package_1;
			Package package_2;

			memcpy(package_1.data, &command_1, sizeof(command_1));
			memcpy(package_2.data, &command_2, sizeof(command_2));

			send(m_sockets[0], package_1);

			receive(m_sockets[0], sizeof(Status) - 1);

			send(m_sockets[1], package_2);

			receive(m_sockets[1], sizeof(Status) - 1);
		}

	private:

		std::uint8_t receive(socket_t& socket, std::size_t length)
		{
			std::uint8_t buffer[1024];

			boost::asio::read(socket, boost::asio::buffer(buffer, length));

			// print_data(buffer, length);

			if (length > 8)
			{
				return (buffer[8]);
			}
			else
			{
				return 0x00;
			}
		}

		void print_data(std::uint8_t* buffer, std::size_t length)
		{
			for (auto i = 0U; i < length; ++i)
			{
				auto c = buffer[i];

				std::uint8_t mask = 128;

				for (auto j = 0U; j < 8U; ++j)
				{
					std::cout << ((mask & c) ? "1" : "0");

					mask >>= 1;
				}

				std::cout << std::endl;
			}

			std::cout << std::endl;
		}

		template < typename T >
		void send(socket_t& socket, T& command)
		{
			update_control_sum(command);

			boost::asio::write(socket, boost::asio::buffer(&command, sizeof(command)));
		}

		template < typename T >
		void update_control_sum(T& command)
		{
			command.control_sum = get_control_sum(
				&command.control_sum, sizeof(command));
		}

		std::uint8_t get_control_sum(std::uint8_t* data, std::uint16_t length)
		{
			std::uint8_t s = 0xFF;

			while (length--)
			{
				s += *(data++);
			}

			return (s ^ 0xFF);
		}

	private:

		static inline const std::uint8_t ok_access = 0x01;

		static inline const std::uint32_t min_speed = 15U;
		static inline const std::uint32_t max_speed = 15600U;

		static inline const std::uint32_t min_acceleration = 15U;
		static inline const std::uint32_t max_acceleration = 59000U;

	private:

		boost::asio::io_service m_io_service;

		sockets_container_t m_sockets;
	};

} // namespace solution

using Controller = solution::Controller;

int main(int argc, char** argv)
{
	system("chcp 1251");

	try
	{
		{
			Controller controller({
				{ "192.168.1.2", 5000U},
				{ "192.168.1.3", 5001U} });

			char command = ' ';

			while (command != 'e' && command != 'E')
			{
				std::cout << "Enter command (B - backward, S - stop, F - forward, E - exit) : ";

				std::cin >> command;

				switch (command)
				{
				case 'f': case 'F': case 'b': case 'B':
				{
					std::uint32_t speed = 0U;
					std::uint32_t acceleration = 0U;

					std::cin >> speed >> acceleration;

					controller.set_acceleration(acceleration);

					controller.move(command, speed);

					break;
				}
				case 's': case 'S':
				{
					controller.stop();

					break;
				}
				default:
				{
					break;
				}
				}
			}
		}

		system("pause");

		return EXIT_SUCCESS;
	}
	catch (const std::exception& exception)
	{
		std::cerr << exception.what() << std::endl;

		system("pause");

		return EXIT_FAILURE;
	}
	catch (...)
	{
		std::cerr << "unknown exception" << std::endl;

		system("pause");

		return EXIT_FAILURE;
	}
}