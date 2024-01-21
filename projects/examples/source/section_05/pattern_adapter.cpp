#include <iostream>

struct Device {	void run() const { std::cout << "Device\n"; } };

class Computer
{
public:

	virtual ~Computer() = default; // note: polymorphic base class

	virtual void run() const = 0;
	
}; // class Computer

class Adapter : public Computer
{
public:

	explicit Adapter(const Device & device) : m_device(device) {}

	void run() const override { m_device.run(); }

private:

	const Device & m_device; // note: consider additional settings

}; // class Adapter : public Computer

int main()
{
	Device device; Computer * computer = new Adapter(device);

	computer->run(); delete computer;

	return 0;
}