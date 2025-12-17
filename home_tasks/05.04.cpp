#include <iostream>
#include <string>

template <typename T>
class Entity : private T {
public:
    using T::T;
    
    void execute() const {
        T::execute();
    }
    
    void process(const std::string& data) const {
        T::process(data);
    }
};

class ConcreteStrategyA {
public:
    void execute() const {
        std::cout << "Strategy A: выполнение\n";
    }
    
    void process(const std::string& data) const {
        std::cout << "Strategy A обработка: " << data << "\n";
    }
};

class ConcreteStrategyB {
public:
    ConcreteStrategyB(int param = 0) : parameter(param) {}
    
    void execute() const {
        std::cout << "Strategy B: выполнение с параметром " << parameter << "\n";
    }
    
    void process(const std::string& data) const {
        std::cout << "Strategy B обработка: " << data 
                  << " (параметр: " << parameter << ")\n";
    }
    
private:
    int parameter;
};

class FastStrategy {
public:
    FastStrategy(const std::string& name = "default") : strategyName(name) {}
    
    void execute() const {
        std::cout << "Быстрая стратегия '" << strategyName << "'\n";
    }
    
    void process(const std::string& data) const {
        std::cout << "Быстрая обработка '" << strategyName 
                  << "': " << data << "\n";
    }
    
    void specialMethod() const {
        std::cout << "Специальный метод быстрой стратегии\n";
    }
    
private:
    std::string strategyName;
};

int main() {
    
    Entity<ConcreteStrategyA> entity1;
    std::cout << "1. Entity с StrategyA:\n";
    entity1.execute();
    entity1.process("тестовые данные");
    std::cout << "\n";
    
    Entity<ConcreteStrategyB> entity2(42);
    std::cout << "2. Entity с StrategyB:\n";
    entity2.execute();
    entity2.process("информация");
    std::cout << "\n";
    
    Entity<FastStrategy> entity3("моя_стратегия");
    std::cout << "3. Entity с FastStrategy:\n";
    entity3.execute();
    entity3.process("данные для обработки");
    
    return 0;
}