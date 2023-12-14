#include <iostream>
#include <vector>

class Observer 
{
public:

    virtual ~Observer() = default;

    virtual void update(double temperature) const = 0;

}; // class Observer 

class Weather_Station 
{
public:

    explicit Weather_Station() : m_temperature(0.0) {}

    ~Weather_Station()
    {
        for (std::size_t i = 0; i < m_observers.size(); ++i)
        {
            delete m_observers[i]; // good: no memory leak
        }
    }

public:

    void set_temperature(double temperature) 
    {
        m_temperature = temperature;
        
        notify_all();
    }

    void notify_all() const 
    { 
        for (std::size_t i = 0; i < m_observers.size(); ++i)
        {
            if (m_observers[i]) // good: verify if nullptr
            {
                m_observers[i]->update(m_temperature);
            }
        }
    }

    void add_observer(Observer * observer)
    {
        m_observers.push_back(observer);
    }

private:

    double m_temperature;

    std::vector < Observer * > m_observers;

}; // class Weather_Station 

class Display_1 : public Observer 
{
public:

    void update(double temperature) const
    {
        std::cout << "Display_1: temperature = " << temperature << std::endl;
    }

}; // class Display_1 : public Observer 

class Display_2 : public Observer
{
public:

    void update(double temperature) const
    {
        std::cout << "Display_2: temperature = " << temperature << std::endl;
    }

}; // class Display_2 : public Observer 

int main() 
{
    Weather_Station weather_station;

    weather_station.add_observer(new Display_1);
    weather_station.add_observer(new Display_2);

    weather_station.set_temperature(25.5);
    weather_station.set_temperature(24.8);

    return 0;
}