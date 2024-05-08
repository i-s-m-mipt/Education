#include <iostream>
#include <vector>

//  ================================================================================================

class Computer
{
public:

    virtual ~Computer() = default; 

    [[nodiscard]] virtual std::size_t cores() const = 0;

}; // class Computer

//  ================================================================================================

class Mobile : public Computer { public: [[nodiscard]] std::size_t cores() const override; };
class Tablet : public Computer { public: [[nodiscard]] std::size_t cores() const override; };
class Laptop : public Computer { public: [[nodiscard]] std::size_t cores() const override; };

//  ================================================================================================

[[nodiscard]] std::size_t Mobile::cores() const { return 1; }
[[nodiscard]] std::size_t Tablet::cores() const { return 2; }
[[nodiscard]] std::size_t Laptop::cores() const { return 3; }

//  ================================================================================================

class Cluster : public Computer
{
public:

   ~Cluster()
    {
        for (const auto computer : m_computers) delete computer;
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

//  ================================================================================================

[[nodiscard]] const Computer * make_cluster(std::size_t n_mobiles, 
                                            std::size_t n_tablets, 
                                            std::size_t n_laptops)
{
    const auto cluster = new Cluster;

    for (std::size_t i = 0; i < n_mobiles; ++i) cluster->add_computer(new const Mobile());
    for (std::size_t i = 0; i < n_tablets; ++i) cluster->add_computer(new const Tablet());
    for (std::size_t i = 0; i < n_laptops; ++i) cluster->add_computer(new const Laptop());

    return cluster;
}

//  ================================================================================================

int main()
{
    const auto super_cluster = new Cluster;

    for (std::size_t i = 0; i < 4; ++i) super_cluster->add_computer(make_cluster(1, 1, 1));

    const Computer * const computer = super_cluster;
        
    std::cout << computer->cores() << std::endl;

    delete computer;

    return 0;
}