#include <iostream>

class Computer
{
public:

    virtual ~Computer() = default;

public:

    virtual double performance() const = 0;

}; // class Computer

class Laptop : public Computer
{
public:

    double performance() const override { return 1.0; }

}; // class Laptop : public Computer

class Desktop : public Computer
{
public:

    double performance() const override { return 10.0; }

}; // class Desktop : public Computer

class Server : public Computer
{
public:

    double performance() const override { return 100.0; }

}; // class Server : public Computer

class Cluster : public Computer // note: composite of computers
{
public:

    ~Cluster()
    {
        for (auto i = 0; i < m_counter; ++i)
        {
            delete m_computers[i]; // good: no memory leak
        }
    }

public:

    double performance() const override 
    {
        auto total_performance = 0.0;

        for (auto i = 0; i < m_counter; ++i)
        {
            if (m_computers[i]) // good: verify if nullptr
            {
                total_performance += m_computers[i]->performance();
            }
        }

        return total_performance;
    }

    [[nodiscard]] bool add_computer(Computer * computer)
    {
        if (m_counter < max_computers)
        {
            m_computers[m_counter++] = computer;

            return true;
        }
        else
        {
            return false;
        }
    }

private:

    static inline const int max_computers = 100;

private:

    int m_counter = 0;

    Computer * m_computers[max_computers]{};

}; // class Cluster : public Computer

[[nodiscard]] auto make_cluster(int size)
{
    auto cluster = new Cluster;

    for (auto i = 0; i < size; ++i)
    {
        Computer * computer = new Server;

        if (!cluster->add_computer(computer)) 
        { 
            delete computer; // good: no memory leak
        } 
    }

    return cluster;
}

int main()
{
    const auto size = 4;

    auto super_cluster = new Cluster;

    for (auto i = 0; i < size; ++i)
    {
        Computer * computer = make_cluster(size * 2);

        if (!super_cluster->add_computer(computer)) 
        { 
            delete computer; // good: no memory leak
        } 
    }

    Computer * computer = super_cluster;
        
    std::cout << computer->performance() << std::endl;

    delete computer; // good: no memory leak

    return 0;
}