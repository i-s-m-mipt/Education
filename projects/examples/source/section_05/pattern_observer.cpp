#include <iostream>
#include <vector>

class Observer 
{
public:

    virtual ~Observer() = default; // note: polymorphic base class

    virtual void update(double temperature) const = 0;

}; // class Observer 

class Computer 
{
public:

    ~Computer()
    {
        for (const auto observer : m_observers) delete observer; // good: no memory leak
    }

    void set_temperature(double temperature) 
    {
        m_temperature = temperature; notify_all();
    }

    void notify_all() const 
    { 
        for (const auto observer : m_observers)
        {
            if (observer) observer->update(m_temperature);
        }
    }

    void add_observer(const Observer * observer) { m_observers.push_back(observer); }

private:

    double m_temperature = 0.0; std::vector < const Observer * > m_observers;

}; // class Computer 

class Display_1 : public Observer 
{
public:

    void update(double temperature) const override
    {
        std::cout << "Display 1: temperature = " << temperature << std::endl;
    }

}; // class Display_1 : public Observer 

class Display_2 : public Observer
{
public:

    void update(double temperature) const override
    {
        std::cout << "Display 2: temperature = " << temperature << std::endl;
    }

}; // class Display_2 : public Observer 

int main() 
{
    Computer computer;

    computer.add_observer(new Display_1);
    computer.add_observer(new Display_2);

    computer.set_temperature(25.5);
    computer.set_temperature(24.8);

    return 0;
}