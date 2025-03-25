#include <cassert>

/////////////////////////////////////////////////

class Entity
{
public :

    auto get() const 
    { 
        return m_x;
    }
    
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
        m_x = B::get();
        
        B::set(x);
    }

    auto & undo() 
    { 
        B::set(m_x);

        return *this;
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
        m_x = x;
        
        B::set(x);
    }

    auto & redo() 
    { 
        B::set(m_x);

        return *this;
    }
    
private :
    
    int m_x = 0;
};

/////////////////////////////////////////////////

int main() 
{
    Redoable < Undoable < Entity > > entity;

//  ----------------------------------------

    for (auto i = 0; i < 2; ++i)
    {
        entity.set(i + 1);
    }

//  ----------------------------------------

    assert(entity.undo().get() == 1);

    assert(entity.redo().get() == 2);
}