#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <optional>
#include <algorithm>
#include <thread>
#include <stdexcept>

class DynamicArray {
private:
    int* m_data;
    size_t m_size;
    size_t m_capacity;

public:
    // 1st Default Constructor
    DynamicArray(){
        m_size=0;
        m_capacity = 5;
        m_data = new int[m_capacity];
    }

    // 2nd Deconstructor
    ~DynamicArray(){
        delete[] m_data;
    }
    // 3rd Parameterized Constructor
    DynamicArray(int s){
        m_size=0;
        m_capacity=s;
        m_data = new int[m_capacity];
    }
    // 4th size fn
    int size(){
        return m_size;
    }
    // 5th capacity
    int capacity(){
        return m_capacity;
    }
    
    // 6th empty check
    bool empty(){
        return m_size==0;
    }

    // 7th look up from index
    int lookup(int index){
        if(index>=m_size){
            throw std::out_of_range("Index out of bounds: Attempt to access index "+ std::to_string(index));
        }
        else{
            return m_data[index];
        }
    }

    // 8th push_back
    void push_back(int value){
        //Only considering that capacity!=size
        m_data[m_size++] = value;
    }

    // 9th pop_back
    void pop_back(){
        m_size--;
    }

    // 10th clearing all elements
    void clear(){
        m_size=0;
    }
};

int main(){
    DynamicArray ma;
    std::cout<<ma.size()<<std::endl;
    ma.push_back(10);
    std::cout<<ma.lookup(0)<<std::endl;
    std::cout<<ma.size()<<std::endl;
    ma.pop_back();
    std::cout<<ma.size();
    // std::cout<<ma.lookup(5);

    return 1;
}
