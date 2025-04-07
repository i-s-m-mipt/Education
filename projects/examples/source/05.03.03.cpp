/////////////////////////////////////////////////////////////////////////

#include <iostream>

/////////////////////////////////////////////////////////////////////////

class State
{
public :

    virtual ~State() = default;

//  ------------------------------------------------

    virtual void set_slow(class Entity *) const = 0;

    virtual void set_fast(class Entity *) const = 0;
};

/////////////////////////////////////////////////////////////////////////

class Slow : public State 
{ 
public :

    void set_slow([[maybe_unused]] class Entity * entity) const override;

    void set_fast([[maybe_unused]] class Entity * entity) const override;
};

/////////////////////////////////////////////////////////////////////////

class Fast : public State 
{ 
public :

    void set_slow([[maybe_unused]] class Entity * entity) const override;

    void set_fast([[maybe_unused]] class Entity * entity) const override;
};

/////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    Entity() : m_state(new Slow) {}

//  --------------------------------------------

   ~Entity() 
    { 
        set_state(nullptr);
    }

//  --------------------------------------------

    void set_state(State * state) 
    { 
        if (m_state)
        {
            delete m_state;
        }
        
        m_state = state;
    }

//  --------------------------------------------

    void set_slow() { m_state->set_slow(this); }

    void set_fast() { m_state->set_fast(this); }

private :

    State * m_state = nullptr;
};

/////////////////////////////////////////////////////////////////////////

void Slow::set_slow([[maybe_unused]] Entity * entity) const
{
    std::cout << "Slow::set_slow\n";
}

/////////////////////////////////////////////////////////////////////////

void Slow::set_fast([[maybe_unused]] Entity * entity) const
{
    std::cout << "Slow::set_fast\n";

//  --------------------------------
    
    entity->set_state(new Fast);
}

/////////////////////////////////////////////////////////////////////////

void Fast::set_slow([[maybe_unused]] Entity * entity) const
{
    std::cout << "Fast::set_slow\n";

//  --------------------------------
    
    entity->set_state(new Slow);
}

/////////////////////////////////////////////////////////////////////////

void Fast::set_fast([[maybe_unused]] Entity * entity) const
{
    std::cout << "Fast::set_fast\n";
}

/////////////////////////////////////////////////////////////////////////

int main()
{
    Entity entity;

//  ------------------

    entity.set_slow();
    
    entity.set_fast();

    entity.set_fast();

    entity.set_slow();
}

/////////////////////////////////////////////////////////////////////////