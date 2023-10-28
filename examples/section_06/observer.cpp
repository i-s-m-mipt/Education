#include <iostream>

class Observer 
{
public:

    virtual void update(double temperature) const = 0;

}; // class Observer 

class Weather_Station 
{
public:

    explicit Weather_Station(Observer * observer) : 
        m_temperature(0.0), m_observer(observer)
    {
        if (!m_observer) // good: verify if nullptr
        {
            std::cout << "invalid observer" << std::endl;
        }
    }

public:

    void set_temperature(double temperature) 
    {
        m_temperature = temperature;
        
        notify();
    }

    void notify() const { m_observer->update(m_temperature); }

private:

    double m_temperature;

    Observer * m_observer;

}; // class Weather_Station 

class Display : public Observer 
{
public:

    void update(double temperature) const
    {
        std::cout << "Temperature: " << temperature << std::endl;
    }

}; // class Display : public Observer 

int main() 
{
    Observer * observer = new Display;

    Weather_Station weather_station(observer);

    weather_station.set_temperature(25.5);
    weather_station.set_temperature(24.8);

    delete observer; // good: no memory leak

    return 0;
}