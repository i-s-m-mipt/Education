#include <iostream>
#include <string>

class Person {
private:
    std::string name_;
    int age_;
    int grade_;
    
    // Приватный конструктор - только Builder может создавать Person
    Person(const std::string& name, int age, int grade)
        : name_(name), age_(age), grade_(grade) {}
    
    // Делаем Builder дружественным классом
    friend class Builder;

public:
    void print() const {
        std::cout << "Person: name = " << name_ 
                  << ", age = " << age_ 
                  << ", grade = " << grade_ << std::endl;
    }
};

class Builder {
private:
    std::string name_ = "";  // значения по умолчанию
    int age_ = 0;
    int grade_ = 0;

public:
    // Конструктор по умолчанию
    Builder() = default;
    
    // Методы для поэтапного создания (возвращают *this для цепочки вызовов)
    Builder& name(const std::string& name) {
        name_ = name;
        return *this;
    }
    
    Builder& age(int age) {
        age_ = age;
        return *this;
    }
    
    Builder& grade(int grade) {
        grade_ = grade;
        return *this;
    }
    
    // Метод для получения созданного объекта
    Person get() {
        return Person(name_, age_, grade_);
    }
};

int main() {
    Builder builder;
    auto person = builder.name("Ivan").age(25).grade(10).get();
    person.print();
    
    Person person2 = Builder().name("Anna").age(30).grade(8).get();
    person2.print();
    
    Person person3 = Builder().grade(12).name("Peter").age(18).get();
    person3.print();
    
    Builder b;
    b.name("Maria");
    b.age(22);
    b.grade(9);
    Person person4 = b.get();
    person4.print();
    
    Person defaultPerson = Builder().get();
    defaultPerson.print();
    
    return 0;
}