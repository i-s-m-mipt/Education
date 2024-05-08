#include <iostream>

//  ================================================================================================

class Computer;

class State
{
public:

    virtual ~State() = default; 

    virtual void stop(Computer *) const { std::cout << "stop" << std::endl; }
    virtual void slow(Computer *) const { std::cout << "slow" << std::endl; }
    virtual void fast(Computer *) const { std::cout << "fast" << std::endl; }

}; // class State

//  ================================================================================================

class Stop : public State
{
public:

    void slow([[maybe_unused]] Computer * computer) const override;
    void fast([[maybe_unused]] Computer * computer) const override;

}; // class Stop : public State

//  ================================================================================================

class Slow : public State
{
public:

    void stop([[maybe_unused]] Computer * computer) const override;
    void fast([[maybe_unused]] Computer * computer) const override;

}; // class Slow : public State

//  ================================================================================================

class Fast : public State
{
public:

    void stop([[maybe_unused]] Computer * computer) const override;
    void slow([[maybe_unused]] Computer * computer) const override;

}; // class Fast : public State

//  ================================================================================================

class Computer // support: конечные автоматы
{
public:

    Computer() : m_state(new const Stop()) {}

   ~Computer() { set_state(nullptr); }

    void set_state(const State * state) 
    { 
        delete m_state; m_state = state;
    }

    void stop() { m_state->stop(this); }
    void slow() { m_state->slow(this); }
    void fast() { m_state->fast(this); }

private:

    const State * m_state;

}; // class Computer

//  ================================================================================================

void Stop::slow([[maybe_unused]] Computer * computer) const
{
    computer->set_state(new const Slow()); std::cout << "stop -> slow" << std::endl;
}

void Stop::fast([[maybe_unused]] Computer * computer) const
{
    std::cout << "stop -> fast unavailable" << std::endl;
}

//  ================================================================================================

void Slow::stop([[maybe_unused]] Computer * computer) const
{
    computer->set_state(new const Stop()); std::cout << "slow -> stop" << std::endl;
}

void Slow::fast([[maybe_unused]] Computer * computer) const
{
    computer->set_state(new const Fast()); std::cout << "slow -> fast" << std::endl;
}

//  ================================================================================================

void Fast::stop([[maybe_unused]] Computer * computer) const
{
    std::cout << "fast -> stop unavailable" << std::endl;
}

void Fast::slow([[maybe_unused]] Computer * computer) const
{
    computer->set_state(new const Slow()); std::cout << "fast -> slow" << std::endl;
}

//  ================================================================================================

int main()
{
    Computer computer;

    computer.stop();
    computer.fast();
    computer.slow();
    computer.fast();
    computer.fast();
    computer.stop();
    computer.slow();
    computer.stop();

    return 0;
}