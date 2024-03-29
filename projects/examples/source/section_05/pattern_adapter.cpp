#include <iostream>

class Device { public: void run() const { std::cout << "Device" << std::endl; } };

class Computer
{
public:

	virtual ~Computer() = default; // note: polymorphic base class

	virtual void run() const = 0;
	
}; // class Computer

class Adapter : public Computer // note: consider private Device
{
public:

	explicit Adapter(const Device & device) : m_device(device) {}

	void run() const override { m_device.run(); }

private:

	const Device & m_device; // note: consider additional settings

}; // class Adapter : public Computer

int main()
{	
	const Computer * const computer = new Adapter(Device());

	computer->run(); 
	
	delete computer; // good: no memory leak

	return 0;
}