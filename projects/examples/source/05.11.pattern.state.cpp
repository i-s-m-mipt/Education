#include <iostream>

// =================================================================================================

class Computer; // note: forward declaration for pointers

class State
{
public:

    virtual ~State() = default; // note: polymorphic base class

    virtual void stop([[maybe_unused]] Computer * c) const { std::cout << "stop already" << std::endl; }
    virtual void slow([[maybe_unused]] Computer * c) const { std::cout << "slow already" << std::endl; }
    virtual void fast([[maybe_unused]] Computer * c) const { std::cout << "fast already" << std::endl; }

}; // class State

// =================================================================================================

class Stop : public State // note: implements all possible state changes
{
public:

    void slow([[maybe_unused]] Computer * c) const override;
    void fast([[maybe_unused]] Computer * c) const override;

}; // class Stop : public State

// =================================================================================================

class Slow : public State // note: implements all possible state changes
{
public:

    void stop([[maybe_unused]] Computer * c) const override;
    void fast([[maybe_unused]] Computer * c) const override;

}; // class Slow : public State

// =================================================================================================

class Fast : public State // note: implements all possible state changes
{
public:

    void stop([[maybe_unused]] Computer * c) const override;
    void slow([[maybe_unused]] Computer * c) const override;

}; // class Fast : public State

// =================================================================================================

class Computer
{
public:

     Computer() : m_state(new Stop()) {} // note: initial state

    ~Computer() { set_state(nullptr); }

    void set_state(const State * state) 
    { 
        delete m_state; m_state = state; // good: no memory leak
    }

    void stop() { m_state->stop(this); }
    void slow() { m_state->slow(this); }
    void fast() { m_state->fast(this); }

private:

    const State * m_state; // note: internal state of state machine

}; // class Computer

// =================================================================================================

void Stop::slow([[maybe_unused]] Computer * c) const
{
    c->set_state(new Slow()); std::cout << "stop -> slow" << std::endl;
}

void Stop::fast([[maybe_unused]] Computer * c) const
{
    std::cout << "stop -> fast unavailable" << std::endl;
}

void Slow::stop([[maybe_unused]] Computer * c) const
{
    c->set_state(new Stop()); std::cout << "slow -> stop" << std::endl;
}

void Slow::fast([[maybe_unused]] Computer * c) const
{
    c->set_state(new Fast()); std::cout << "slow -> fast" << std::endl;
}

void Fast::stop([[maybe_unused]] Computer * c) const
{
    std::cout << "fast -> stop unavailable" << std::endl;
}

void Fast::slow([[maybe_unused]] Computer * c) const
{
    c->set_state(new Slow()); std::cout << "fast -> slow" << std::endl;
}

// =================================================================================================

int main()
{
    Computer c;

    c.stop();
    c.fast();
    c.slow();
    c.fast();
    c.fast();
    c.stop();
    c.slow();
    c.stop();

    return 0;
}