////////////////////////////////////////////////////////////////////////

// chapter : Software Design Patterns

////////////////////////////////////////////////////////////////////////

// section : Behavioral Patterns

////////////////////////////////////////////////////////////////////////

// content : Pattern State
//
// content : Finite-State Machines

////////////////////////////////////////////////////////////////////////

#include <print>
#include <utility>

////////////////////////////////////////////////////////////////////////

class State
{
public :

    virtual ~State() = default;

//  -----------------------------------------------

    virtual void to_slow(class Entity *) const = 0;

    virtual void to_fast(class Entity *) const = 0;
};

////////////////////////////////////////////////////////////////////////

class Slow : public State 
{ 
public :

    void to_slow([[maybe_unused]] class Entity * entity) const override;

    void to_fast([[maybe_unused]] class Entity * entity) const override;
};

////////////////////////////////////////////////////////////////////////

class Fast : public State 
{ 
public :

    void to_slow([[maybe_unused]] class Entity * entity) const override;

    void to_fast([[maybe_unused]] class Entity * entity) const override;
};

////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    Entity() : m_state(new Slow) {}

//  ------------------------------------------

   ~Entity() 
    { 
        set(nullptr);
    }

//  ------------------------------------------

    void set(State * state)
    { 
        delete std::exchange(m_state, state);
    }

//  ------------------------------------------

    void to_slow() { m_state->to_slow(this); }

    void to_fast() { m_state->to_fast(this); }

private :

    State * m_state = nullptr;
};

////////////////////////////////////////////////////////////////////////

void Slow::to_slow([[maybe_unused]] Entity * entity) const
{
    std::print("Slow::to_slow\n");
}

////////////////////////////////////////////////////////////////////////

void Slow::to_fast([[maybe_unused]] Entity * entity) const
{
    std::print("Slow::to_fast\n");
    
    entity->set(new Fast);
}

////////////////////////////////////////////////////////////////////////

void Fast::to_slow([[maybe_unused]] Entity * entity) const
{
    std::print("Fast::to_slow\n");
    
    entity->set(new Slow);
}

////////////////////////////////////////////////////////////////////////

void Fast::to_fast([[maybe_unused]] Entity * entity) const
{
    std::print("Fast::to_fast\n");
}

////////////////////////////////////////////////////////////////////////

int main()
{
    Entity entity;

//  -----------------

    entity.to_slow();
    
    entity.to_fast();

    entity.to_fast();

    entity.to_slow();
}

////////////////////////////////////////////////////////////////////////