#include <iostream>
#include <string>

//  ================================================================================================

class Computer 
{
public:

    virtual ~Computer() = default; 

    [[nodiscard]] virtual std::string description() const = 0;

}; // class Computer 

//  ================================================================================================

class Mobile : public Computer { public: [[nodiscard]] std::string description() const override; };
class Tablet : public Computer { public: [[nodiscard]] std::string description() const override; };
class Laptop : public Computer { public: [[nodiscard]] std::string description() const override; };

//  ================================================================================================

[[nodiscard]] std::string Mobile::description() const { return "Mobile"; }
[[nodiscard]] std::string Tablet::description() const { return "Tablet"; }
[[nodiscard]] std::string Laptop::description() const { return "Laptop"; }

//  ================================================================================================

class Decorated_Computer : public Computer
{
public:

    explicit Decorated_Computer(const Computer & computer): m_computer(computer) {}

    [[nodiscard]] std::string description() const override { return m_computer.description(); }

protected:

    const Computer & m_computer;

}; // class Decorated_Computer : public Computer 

//  ================================================================================================

class Overclocked_Computer : public Decorated_Computer
{
public:

    explicit Overclocked_Computer(const Computer & computer) : Decorated_Computer(computer) {}

    [[nodiscard]] std::string description() const override
    { 
        return "Overclocked " + m_computer.description();
    }

}; // class Overclocked_Computer : public Decorated_Computer

//  ================================================================================================

int main()
{
    const Computer * const mobile = new const Mobile();

    std::cout << mobile->description() << std::endl;

    const Computer * const overclocked_mobile = new const Overclocked_Computer(*mobile);

    std::cout << overclocked_mobile->description() << std::endl;

    delete overclocked_mobile; delete mobile;

    return 0;
}