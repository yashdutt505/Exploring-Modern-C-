#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <optional>
#include <algorithm>
#include <thread>
#include <stdexcept>
#include <cstddef>

class DynamicArray
{
private:
    int *m_data;
    size_t m_size;
    size_t m_capacity;

public:
    // 1st Default Constructor
    DynamicArray()
    {
        m_size = 0;
        m_capacity = 2;
        m_data = new int[m_capacity];
    }

    // 2nd Deconstructor
    ~DynamicArray()
    {
        delete[] m_data;
    }
    // 3rd Parameterized Constructor
    DynamicArray(int s)
    {
        m_size = 0;
        m_capacity = s;
        m_data = new int[m_capacity];
    }
    // 4th size fn
    size_t size()
    {
        return m_size;
    }
    // 5th capacity
    size_t capacity()
    {
        return m_capacity;
    }

    // 6th empty check
    bool empty()
    {
        return m_size == 0;
    }

    // 7th look up from index
    int lookup(int index)
    {
        if (index >= m_size)
        {
            throw std::out_of_range("Index out of bounds: Attempt to access index " + std::to_string(index));
        }
        else
        {
            return m_data[index];
        }
    }

    // 8th push_back
    void push_back(int value)
    {
        //If capacity is full, we need to resize and then push.
        if(!(m_size<m_capacity))resize();            
        m_data[m_size++] = value;    
    }

    // 9th pop_back
    void pop_back()
    {
        if (m_size == 0)
        {
            std::cout << "Operation cannot be performed. Trying to remove from empty array";
            return;
        }
        m_size--;
    }

    // 10th clearing all elements
    void clear()
    { // We would also like to free up all the extra memory and return capacity to its starting configuration , 2
        m_size = 0;
        m_capacity = 2;
        int *newarr = new int[m_capacity];
        delete[] m_data;
        m_data = newarr;
    }

    // 11th resizing array - Increases capacity
    void resize()
    {
        // 1. Calculate new capacity safely
        const size_t max_capacity = std::numeric_limits<size_t>::max() / sizeof(int);

        if (m_capacity >= max_capacity)
        {
            throw std::length_error("DynamicArray capacity exceeded");
        }

        const size_t new_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;

        if (new_capacity > max_capacity)
        {
            throw std::length_error("DynamicArray capacity exceeded");
        }

        // 2. Allocate new memory
        int *newarr = new int[new_capacity];

        // 3. Copy existing elements
        for (size_t i = 0; i < m_size; i++)
        {
            newarr[i] = m_data[i];
        }

        // 4. Release old memory
        delete[] m_data;

        // 5. Commit new state
        m_data = newarr;
        m_capacity = new_capacity;
    }

    // 12th resizing to a know size
    void resize(int newcapa)
    { // This function assumes we are fitting capacity to match the size.
        const size_t new_capacity = newcapa;
        int *newarr = new int[new_capacity];
        for (size_t i = 0; i < m_size; i++)
        {
            newarr[i] = m_data[i];
        }
        delete[] m_data;
        m_data = newarr;
        m_capacity = new_capacity;
    }

    // 13th shrink to fit size
    void shrink_to_fit()
    {
        resize(m_size);
    }
};

int main()
{
    DynamicArray ma;
    std::cout << ma.size() << std::endl;
    ma.push_back(10);
    std::cout << ma.lookup(0) << std::endl;
    std::cout << ma.size() << std::endl;
    ma.pop_back();
    std::cout << ma.size();
    // std::cout<<ma.lookup(5);

    return 1;
}
