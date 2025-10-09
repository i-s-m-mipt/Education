#include <atomic>

class Mutex
{ 
public :

    void lock()
    {
        while (m_x.exchange(true, std::memory_order::acquire));
    }

//  -----------------------------------------------------------

    void unlock()
    {
        m_x.store(false, std::memory_order::release);
    }

private :

    std::atomic < bool > m_x = false;
};