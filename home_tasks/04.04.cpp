#include <algorithm>
#include <iostream>
#include <initializer_list>

template <typename T>
class Vector
{
public:
    Vector() : m_array(nullptr), m_capacity(0), m_size(0) 
    {
        std::cout << "Vector:: Vector (1)\n";
    }

    Vector(std::initializer_list<T> list) : m_capacity(list.size()), m_size(list.size())
    {
        std::cout << "Vector:: Vector (2)\n";

        m_array = m_capacity ? new T[m_capacity]{} : nullptr;
        std::copy(list.begin(), list.end(), m_array);
    }

    Vector(Vector const& other) : m_capacity(other.m_size), m_size(other.m_size)
    {
        std::cout << "Vector:: Vector (3)\n";

        m_array = m_capacity ? new T[m_capacity]{} : nullptr;
        std::copy(other.m_array, other.m_array + other.m_size, m_array);
    }

    Vector(Vector&& other)
        : m_array(std::exchange(other.m_array, nullptr)),
        m_capacity(std::exchange(other.m_capacity, 0)),
        m_size(std::exchange(other.m_size, 0))
    {
        std::cout << "Vector:: Vector (4)\n";
    }

    ~Vector()
    {
        std::cout << "Vector::~Vector\n";
        delete[] m_array;
    }

    auto& operator=(Vector other)
    {
        std::cout << "Vector::operator=\n";
        swap(other);
        return *this;
    }

    void swap(Vector& other)
    {
        std::swap(m_array, other.m_array);
        std::swap(m_capacity, other.m_capacity);
        std::swap(m_size, other.m_size);
    }

    std::size_t capacity() const { return m_capacity; }
    std::size_t size() const { return m_size; }
    bool empty() const { return m_size == 0; }

    void push_back(T value)
    {
        if (m_size >= m_capacity)
        {
            std::size_t new_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
            
            T* new_array = new T[new_capacity]{};
            
            if (m_array && m_size > 0)
            {
                std::copy(m_array, m_array + m_size, new_array);
                delete[] m_array;
            }
            
            m_array = new_array;
            m_capacity = new_capacity;
        }
        
        m_array[m_size] = value;
        ++m_size;
    }

    void clear()
    {
        m_size = 0;
    }

private:
    T* m_array = nullptr;
    std::size_t m_capacity = 0;
    std::size_t m_size = 0;
};

int main() {
    std::cout << "=== Testing Vector class ===\n\n";
    
    // Test 1: Default constructor
    std::cout << "1. Default constructor:\n";
    Vector<int> v1;
    std::cout << "   Size: " << v1.size() << ", Capacity: " << v1.capacity() << ", Empty: " << v1.empty() << "\n\n";
    
    // Test 2: Initializer list
    std::cout << "2. Initializer list {1, 2, 3}:\n";
    Vector v2 = {1, 2, 3};
    std::cout << "   Size: " << v2.size() << ", Capacity: " << v2.capacity() << ", Empty: " << v2.empty() << "\n\n";
    
    // Test 3: Push back with capacity growth
    std::cout << "3. Push back (capacity growth):\n";
    Vector<int> v3;
    for (int i = 1; i <= 5; i++) {
        v3.push_back(i * 10);
        std::cout << "   Added " << i * 10 << " -> Size: " << v3.size() << ", Capacity: " << v3.capacity() << "\n";
    }
    std::cout << "\n";
    
    // Test 4: Copy constructor
    std::cout << "4. Copy constructor:\n";
    Vector<int> v4 = v3;
    std::cout << "   Copy size: " << v4.size() << ", capacity: " << v4.capacity() << "\n\n";
    
    // Test 5: Move constructor
    std::cout << "5. Move constructor:\n";
    Vector<int> v5 = std::move(Vector{100, 200});
    std::cout << "   Moved size: " << v5.size() << ", capacity: " << v5.capacity() << "\n\n";
    
    // Test 6: Assignment operator
    std::cout << "6. Assignment operator:\n";
    Vector<int> v6;
    v6 = v2;
    std::cout << "   Assigned size: " << v6.size() << ", capacity: " << v6.capacity() << "\n\n";
    
    // Test 7: Clear
    std::cout << "7. Clear:\n";
    Vector v7 = {1, 2, 3, 4, 5};
    std::cout << "   Before clear - Size: " << v7.size() << ", Capacity: " << v7.capacity() << "\n";
    v7.clear();
    std::cout << "   After clear - Size: " << v7.size() << ", Capacity: " << v7.capacity() << ", Empty: " << v7.empty() << "\n\n";
    
    // Test 8: Empty check
    std::cout << "8. Empty check:\n";
    Vector<int> v8;
    std::cout << "   New vector empty: " << v8.empty() << "\n";
    v8.push_back(42);
    std::cout << "   After push_back empty: " << v8.empty() << "\n";
    v8.clear();
    std::cout << "   After clear empty: " << v8.empty() << "\n\n";
    
    // Test 9: Swap
    std::cout << "9. Swap:\n";
    Vector v9a = {1, 2, 3};
    Vector v9b = {4, 5};
    std::cout << "   Before swap - v9a size: " << v9a.size() << ", v9b size: " << v9b.size() << "\n";
    v9a.swap(v9b);
    std::cout << "   After swap - v9a size: " << v9a.size() << ", v9b size: " << v9b.size() << "\n\n";
    
    std::cout << "=== All tests completed ===\n";
    
    return 0;
}