//////////////////////////////////////////////////////

// chapter : Software Engineering Patterns

//////////////////////////////////////////////////////

// content : Pattern Memento
//
// content : Version Control System Git

//////////////////////////////////////////////////////

#include <cassert>
#include <cstddef>
#include <vector>

//////////////////////////////////////////////////////

class Entity
{
private :

    struct Memento
    {
        int x = 0;
    };

public :

    Entity(int x = 0) : m_mementos(1, Memento())
    {
        set(x);
    }

//  --------------------------------------------------

    auto get() const
    {
        return m_mementos.front().x;
    }

//  --------------------------------------------------

    void set(int x)
    {
        m_mementos.front().x = x;

        m_mementos.push_back(m_mementos.front());
    }

//  --------------------------------------------------

    auto & load(std::size_t index)
    {
        m_mementos.front() = m_mementos.at(index + 1);

        return *this;
    }

private :

    std::vector < Memento > m_mementos;
};

//////////////////////////////////////////////////////

int main()
{
    Entity entity;

//  ----------------------------------

    for (auto i = 1; i < 3; ++i)
    {
        entity.set(i);
    }

//  ----------------------------------

    assert(entity.load(1).get() == 1);
}

//////////////////////////////////////////////////////