#include <iostream>

class Fahrenheit_Sensor
{
public:

	double get_temperature() const { return 451.0; } // note: old interface

}; // class Fahrenheit_Sensor

class Sensor
{
public:

	virtual ~Sensor() = default;

public:

	virtual double get_temperature() const = 0;
	
}; // class Sensor

class Adapter : public Sensor
{
public:

	explicit Adapter(const Fahrenheit_Sensor & sensor) : m_sensor(sensor) {}

public:

	double get_temperature() const override // note: the same interface
	{
		return (m_sensor.get_temperature() - 32.0) * 5.0 / 9.0;
	}

private:

	const Fahrenheit_Sensor & m_sensor;

}; // class Adapter : public Sensor

int main()
{
	Fahrenheit_Sensor old_sensor;

	Sensor * new_sensor = new Adapter(old_sensor);

	std::cout << new_sensor->get_temperature() << std::endl;

	delete new_sensor; // good: no memory leak

	return 0;
}