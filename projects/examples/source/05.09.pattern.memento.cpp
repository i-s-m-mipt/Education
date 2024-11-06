#include <cassert>
#include <string>
#include <vector>

//  ================================================================================================

class Entity 
{
public:

    struct Memento 
    { 
        int data = 0; 
    };

//  ------------------------------------------------------------------------------------------------

    auto data() const 
    { 
        return m_data; 
    }

    void set_data(int data) 
    { 
        m_data = data < 0 ? 0 : data; 
    }

    void save()
    { 
        m_mementos.emplace_back(m_data); 
    }

    void load(std::size_t index) 
    { 
        m_data = m_mementos.at(index).data;
    }

private:

    int m_data = 0; std::vector < Memento > m_mementos;
};

//  ================================================================================================

int main() 
{
    Entity entity; 
    
    entity.set_data(1); entity.save();
    entity.set_data(2); entity.save();
    
    entity.load(0); 
    
    assert(entity.data() == 1);
}