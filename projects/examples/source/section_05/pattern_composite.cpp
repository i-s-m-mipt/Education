#include <iostream>
#include <vector>

class Computer
{
public:

    virtual ~Computer() = default; // note: polymorphic base class

    [[nodiscard]] virtual std::size_t cores() const = 0;

}; // class Computer

class Mobile : public Computer { public: [[nodiscard]] std::size_t cores() const override { return 1; } };
class Tablet : public Computer { public: [[nodiscard]] std::size_t cores() const override { return 2; } };
class Laptop : public Computer { public: [[nodiscard]] std::size_t cores() const override { return 3; } };

class Cluster : public Computer // note: composite class of concrete computers
{
public:

    ~Cluster()
    {
        for (const auto computer : m_computers) delete computer; // good: no memory leak
    }

    [[nodiscard]] std::size_t cores() const override
    {
        std::size_t total_cores = 0;

        for (const auto computer : m_computers)
        {
            if (computer) total_cores += computer->cores();
        }

        return total_cores;
    }

    void add_computer(const Computer * computer) { m_computers.push_back(computer); }

private:
    
    std::vector < const Computer * > m_computers;

}; // class Cluster : public Computer

[[nodiscard]] Computer * make_cluster(std::size_t n_mobiles, std::size_t n_tablets, std::size_t n_laptops)
{
    const auto cluster = new Cluster;

    for (std::size_t i = 0; i < n_mobiles; ++i) cluster->add_computer(new Mobile);
    for (std::size_t i = 0; i < n_tablets; ++i) cluster->add_computer(new Tablet);
    for (std::size_t i = 0; i < n_laptops; ++i) cluster->add_computer(new Laptop);

    return cluster;
}

int main()
{
    const auto super_cluster = new Cluster;

    for (std::size_t i = 0; i < 4; ++i) super_cluster->add_computer(make_cluster(1, 1, 1));

    const Computer * const computer = super_cluster;
        
    std::cout << computer->cores() << std::endl;

    delete computer; // good: no memory leak

    return 0;
}