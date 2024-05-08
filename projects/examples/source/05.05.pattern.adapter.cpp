#include <iostream>

//  ================================================================================================

class Device { public: void run() const { std::cout << "Device" << std::endl; } };

//  ================================================================================================

class Computer
{
public:

	virtual ~Computer() = default; 

	virtual void run() const = 0;
	
}; // class Computer

//  ================================================================================================

class Adapter : public Computer
{
public:

	explicit Adapter(const Device & device) : m_device(device) {}

	void run() const override { m_device.run(); }

private:

	const Device & m_device;

}; // class Adapter : public Computer

//  ================================================================================================

int main()
{	
	const Computer * const computer = new const Adapter(Device());

	computer->run(); 
	
	delete computer;

	return 0;
}