#include <iostream>
#include <vector>

class Backup 
{
public:

    constexpr explicit Backup(int data) : m_data(data) {}

    [[nodiscard]] constexpr int data() const { return m_data; }

private:

    int m_data;

}; // class Backup 

class Computer 
{
public:

    [[nodiscard]] constexpr int data() const { return m_data; }

    constexpr void update() { ++m_data; }

    [[nodiscard]] constexpr Backup make_backup() const { return Backup(m_data); }

    constexpr void load_backup(const Backup & backup) { m_data = backup.data(); }

private:

    int m_data = 0;

}; // class Computer 

class Storage 
{
public:

    constexpr void save(const Backup & backup) { m_backups.push_back(backup); }

    [[nodiscard]] constexpr Backup load(int index) const { return m_backups.at(index); }

private:

    std::vector < Backup > m_backups;

}; // class Storage 

int main() 
{
    Computer computer; Storage storage;

    computer.update(); storage.save(computer.make_backup());
    computer.update(); 
    computer.update(); storage.save(computer.make_backup());
    computer.update(); 
    computer.update(); storage.save(computer.make_backup());

    computer.load_backup(storage.load(1));

    std::cout << computer.data() << std::endl;

    return 0;
}