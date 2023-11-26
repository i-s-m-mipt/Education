#include <iostream>
#include <vector>

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
        for (std::size_t i = 0; i < m_computers.size(); ++i)
        {
            delete m_computers[i]; // good: no memory leak
        }
    }

public:

    double performance() const override 
    {
        auto total_performance = 0.0;

        for (std::size_t i = 0; i < m_computers.size(); ++i)
        {
            if (m_computers[i]) // good: verify if nullptr
            {
                total_performance += m_computers[i]->performance();
            }
        }

        return total_performance;
    }

    void add_computer(Computer * computer)
    {
        m_computers.push_back(computer);
    }

private:
    
    std::vector < Computer * > m_computers;

}; // class Cluster : public Computer

[[nodiscard]] auto make_cluster(int size)
{
    auto cluster = new Cluster;

    for (auto i = 0; i < size; ++i)
    {
        cluster->add_computer(new Server);
    }

    return cluster;
}

int main()
{
    const auto size = 4;

    auto super_cluster = new Cluster;

    for (auto i = 0; i < size; ++i)
    {
        super_cluster->add_computer(make_cluster(size * 2));
    }

    Computer * computer = super_cluster;
        
    std::cout << computer->performance() << std::endl;

    delete computer; // good: no memory leak

    return 0;
}