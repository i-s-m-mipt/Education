////////////////////////////////////////////////////////////////////////////

// chapter : Software Engineering Patterns

////////////////////////////////////////////////////////////////////////////

// content : Pattern State
//
// content : Finite-State Machines

////////////////////////////////////////////////////////////////////////////

#include <print>
#include <utility>

////////////////////////////////////////////////////////////////////////////

class State
{
public :

    virtual ~State() = default;

//  ---------------------------------------------------

    virtual void to_state_v1(class Entity *) const = 0;

    virtual void to_state_v2(class Entity *) const = 0;
};

////////////////////////////////////////////////////////////////////////////

class State_v1 : public State
{
public :

    void to_state_v1([[maybe_unused]] class Entity * entity) const override;

    void to_state_v2([[maybe_unused]] class Entity * entity) const override;
};

////////////////////////////////////////////////////////////////////////////

class State_v2 : public State
{
public :

    void to_state_v1([[maybe_unused]] class Entity * entity) const override;

    void to_state_v2([[maybe_unused]] class Entity * entity) const override;
};

////////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    Entity() : m_state(new State_v1) {}

//  --------------------------------------------------

   ~Entity()
    {
        set(nullptr);
    }

//  --------------------------------------------------

    void set(State * state)
    {
        delete std::exchange(m_state, state);
    }

//  --------------------------------------------------

    void to_state_v1() { m_state->to_state_v1(this); }

    void to_state_v2() { m_state->to_state_v2(this); }

private :

    State * m_state = nullptr;
};

////////////////////////////////////////////////////////////////////////////

void State_v1::to_state_v1([[maybe_unused]] Entity * entity) const
{
    std::print("State_v1::to_state_v1\n");
}

////////////////////////////////////////////////////////////////////////////

void State_v1::to_state_v2([[maybe_unused]] Entity * entity) const
{
    std::print("State_v1::to_state_v2\n");

    entity->set(new State_v2);
}

////////////////////////////////////////////////////////////////////////////

void State_v2::to_state_v1([[maybe_unused]] Entity * entity) const
{
    std::print("State_v2::to_state_v1\n");

    entity->set(new State_v1);
}

////////////////////////////////////////////////////////////////////////////

void State_v2::to_state_v2([[maybe_unused]] Entity * entity) const
{
    std::print("State_v2::to_state_v2\n");
}

////////////////////////////////////////////////////////////////////////////

int main()
{
    Entity entity;

//  ---------------------

    entity.to_state_v1();

    entity.to_state_v2();

    entity.to_state_v2();

    entity.to_state_v1();
}

////////////////////////////////////////////////////////////////////////////