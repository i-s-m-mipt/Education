/////////////////////////////////////////////////

// chapter : Software Engineering Patterns

/////////////////////////////////////////////////

// content : Pattern Inverted Mixin

/////////////////////////////////////////////////

#include <cassert>

/////////////////////////////////////////////////

class Entity
{
public :

    auto get() const
    {
        return m_x;
    }

//  ----------------

    void set(int x)
    {
        m_x = x;
    }

private :

    int m_x = 0;
};

/////////////////////////////////////////////////

template < typename B > class Undoable : public B
{
public :

    void set(int x)
    {
        B::set(m_x = B::get());
    }

//  ---------------------------

    void undo()
    {
        B::set(m_x);
    }

private :

    int m_x = 0;
};

/////////////////////////////////////////////////

template < typename B > class Redoable : public B
{
public :

    void set(int x)
    {
        B::set(m_x = x);
    }

//  --------------------

    void redo()
    {
        B::set(m_x);
    }

private :

    int m_x = 0;
};

/////////////////////////////////////////////////

int main()
{
    Redoable < Undoable < Entity > > entity;

//  -----------------------------------------

    for (auto i = 1; i < 3; ++i)
    {
        entity.set(i);
    }

//  -----------------------------------------

    entity.undo(); assert(entity.get() == 1);

    entity.redo(); assert(entity.get() == 2);
}

/////////////////////////////////////////////////