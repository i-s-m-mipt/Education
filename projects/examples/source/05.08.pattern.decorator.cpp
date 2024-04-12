#include <iostream>
#include <string>

// =================================================================================================

class Computer 
{
public:

    virtual ~Computer() = default; // note: polymorphic base class

    [[nodiscard]] virtual std::string description() const = 0;

}; // class Computer 

// =================================================================================================

class Mobile : public Computer { public: [[nodiscard]] std::string description() const override { return "Mobile"; } };
class Tablet : public Computer { public: [[nodiscard]] std::string description() const override { return "Tablet"; } };
class Laptop : public Computer { public: [[nodiscard]] std::string description() const override { return "Laptop"; } };

// =================================================================================================

class Decorated_Computer : public Computer // note: abstract decorator
{
public:

    explicit Decorated_Computer(const Computer & computer): m_computer(computer) {}

    [[nodiscard]] std::string description() const override { return m_computer.description(); }

protected:

    const Computer & m_computer;

}; // class Decorated_Computer : public Computer 

// =================================================================================================

class Overclocked_Computer : public Decorated_Computer // note: concrete decorator
{
public:

    explicit Overclocked_Computer(const Computer & computer) : Decorated_Computer(computer) {}

    [[nodiscard]] std::string description() const override
    { 
        return "Overclocked " + m_computer.description();
    }

}; // class Overclocked_Computer : public Decorated_Computer

// =================================================================================================

int main()
{
    const Computer * const mobile = new const Mobile();

    std::cout << mobile->description() << std::endl;

    const Computer * const overclocked_mobile = new const Overclocked_Computer(*mobile);

    std::cout << overclocked_mobile->description() << std::endl;

    delete overclocked_mobile; delete mobile; // good: no memory leak

    return 0;
}