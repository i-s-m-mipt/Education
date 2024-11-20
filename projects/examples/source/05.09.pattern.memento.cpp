#include <cassert>
#include <string>
#include <tuple>
#include <vector>

//  =================================================================

class Entity 
{
public:

    explicit Entity(int data = 0) : m_states(1, State(data)) {}

//  -----------------------------------------------------------

    auto get() const
    {
        return m_states.front().data;
    }

    void set(int data)
    {
        State state(data);
        
        m_deltas.push_back(state - m_states.front());

        m_states.front() = state;
    }

    void save()
    { 
        m_states.push_back(m_states.front()); 
    }

    void load_v1(std::size_t index)
    {
        m_states.front() = m_states.at(index);
    }

    void load_v2(std::size_t shift)
    {
        State state;

        for (auto i = 0uz; i < shift && i < std::size(m_deltas); ++i)
        {
            state = state + m_deltas[i];
        }

        m_states.front() = state;
    }

private:

    struct State { int data = 0; };

    struct Delta { int data = 0; };

//  ------------------------------------------------------------

    friend Delta operator-(const State & lhs, const State & rhs) 
    { 
        return Delta(lhs.data - rhs.data); 
    }

    friend State operator+(const State & lhs, const Delta & rhs) 
    { 
        return State(lhs.data + rhs.data); 
    }

//  -------------------------------

    std::vector < State > m_states;

    std::vector < Delta > m_deltas;
};

//  =================================================================

int main() 
{
    Entity entity; 
    
    entity.set(1); entity.save();
    entity.set(2); entity.save();
    
    entity.load_v1(1); assert(entity.get() == 1);
    entity.load_v2(2); assert(entity.get() == 2);
}