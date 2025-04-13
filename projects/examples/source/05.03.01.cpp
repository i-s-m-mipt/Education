////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////

class Memento 
{
public :

    Memento(int x = 0) : m_states(1, State(x)) {}

//  --------------------------------------------------------------------

    auto get() const
    {
        return m_states.front().x;
    }

//  --------------------------------------------------------------------

    void set(int x)
    {
        State state(x);
        
        m_deltas.push_back(state - m_states.front());

        m_states.push_back(state);

        m_states.front() = std::move(state);
    }

//  --------------------------------------------------------------------

    auto & load_v1(std::size_t index)
    {
        m_states.front() = m_states.at(index);

        return *this;
    }

//  --------------------------------------------------------------------

    auto & load_v2(std::size_t index)
    {
        State state;

        for (auto i = 0uz; i < index && i < std::size(m_deltas); ++i)
        {
            state = state + m_deltas[i];
        }

        m_states.front() = state;

        return *this;
    }

private :

    struct State { int x = 0; };

    struct Delta { int x = 0; };

//  --------------------------------------------------------------------

    friend auto operator-(State const & lhs, State const & rhs) -> Delta
    { 
        return Delta(lhs.x - rhs.x);
    }

//  --------------------------------------------------------------------

    friend auto operator+(State const & lhs, Delta const & rhs) -> State
    { 
        return State(lhs.x + rhs.x);
    }

//  --------------------------------------------------------------------

    std::vector < State > m_states;

    std::vector < Delta > m_deltas;
};

////////////////////////////////////////////////////////////////////////

int main() 
{
    Memento memento;

//  --------------------------------------

    for (auto i = 0; i < 2; ++i)
    {
        memento.set(i + 1);
    }

//  --------------------------------------
    
    assert(memento.load_v1(1).get() == 1);
    
    assert(memento.load_v2(2).get() == 2);
}

////////////////////////////////////////////////////////////////////////