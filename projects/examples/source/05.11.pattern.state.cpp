#include <iostream>

//  ================================================================================================

struct State
{
    virtual ~State() = default; 

//  ------------------------------------------------------------------------------------------------

    virtual void set_fast(class Entity *) const = 0;
    virtual void set_slow(class Entity *) const = 0;
};

//  ================================================================================================

struct Fast : public State 
{ 
    void set_fast([[maybe_unused]] class Entity * entity) const override;
    void set_slow([[maybe_unused]] class Entity * entity) const override; 
};

//  ================================================================================================

struct Slow : public State 
{ 
    void set_fast([[maybe_unused]] class Entity * entity) const override;
    void set_slow([[maybe_unused]] class Entity * entity) const override; 
};

//  ================================================================================================

class Entity
{
public:

    Entity() : m_state(new Slow()) {}

   ~Entity() 
    { 
        set_state(nullptr); 
    }

//  ------------------------------------------------------------------------------------------------

    void set_state(State * state) 
    { 
        if (m_state)
        {
            delete m_state;
        }
        
        m_state = state;
    }

//  ------------------------------------------------------------------------------------------------

    void set_fast() { m_state->set_fast(this); }
    void set_slow() { m_state->set_slow(this); }

private:

    State * m_state = nullptr;
};

//  ================================================================================================

void Fast::set_fast([[maybe_unused]] Entity * entity) const
{
    std::clog << "Fast::fast\n";
}

void Fast::set_slow([[maybe_unused]] Entity * entity) const
{
    std::clog << "Fast::slow\n"; entity->set_state(new Slow()); 
}

void Slow::set_fast([[maybe_unused]] Entity * entity) const
{
    std::clog << "Slow::fast\n"; entity->set_state(new Fast());
}

void Slow::set_slow([[maybe_unused]] Entity * entity) const
{
    std::clog << "Slow::slow\n";
}

//  ================================================================================================

int main()
{
    Entity entity;

    entity.set_slow(); 
    entity.set_fast(); 
    entity.set_fast();
    entity.set_slow();
}