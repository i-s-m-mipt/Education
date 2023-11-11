#include <iostream>

class Observer 
{
public:

    virtual void update(double temperature) const = 0;

}; // class Observer 

class Weather_Station 
{
public:

    explicit Weather_Station() : m_temperature(0.0) {}

    ~Weather_Station()
    {
        for (auto i = 0; i < m_counter; ++i)
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
        for (auto i = 0; i < m_counter; ++i)
        {
            if (m_observers[i]) // good: verify if nullptr
            {
                m_observers[i]->update(m_temperature);
            }
        }
    }

    [[nodiscard]] bool add_observer(Observer * observer)
    {
        if (m_counter < max_observers)
        {
            m_observers[m_counter++] = observer;

            return true;
        }
        else
        {
            return false;
        }
    }

private:

    static inline const int max_observers = 100;

private:

    double m_temperature;

    int m_counter = 0;

    Observer * m_observers[max_observers]{};

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
    Observer * observer_1 = new Display_1;
    Observer * observer_2 = new Display_2;

    Weather_Station weather_station;

    if (!weather_station.add_observer(observer_1)) 
    {
        delete observer_1; // good: no memory leak
    }

    if (!weather_station.add_observer(observer_2))
    {
        delete observer_2; // good: no memory leak
    }

    weather_station.set_temperature(25.5);
    weather_station.set_temperature(24.8);

    return 0;
}