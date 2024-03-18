#include <iostream>
#include <vector>

class Backup 
{
public:

    explicit Backup(int data) : m_data(data) {}

    [[nodiscard]] int data() const { return m_data; }

private:

    int m_data;

}; // class Backup 

struct Computer 
{
    [[nodiscard]] Backup make_backup() const { return Backup(data); }

    void load_backup(const Backup & backup) { data = backup.data(); }

    int data;

}; // class Computer 

class Storage 
{
public:

    void save(const Backup & backup) { m_backups.push_back(backup); }

    [[nodiscard]] Backup load(int index) const { return m_backups.at(index); }

private:

    std::vector < Backup > m_backups;

}; // class Storage 

int main() 
{
    Computer computer; Storage storage;

    computer.data = 1; storage.save(computer.make_backup());
    computer.data = 2; 
    computer.data = 3; storage.save(computer.make_backup());
    computer.data = 4; 
    computer.data = 5; storage.save(computer.make_backup());

    computer.load_backup(storage.load(1));

    std::cout << computer.data << std::endl;

    return 0;
}