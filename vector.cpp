#include <iostream>
#include <initializer_list>
#include <stdexcept>

namespace myVec {



template<typename T>
class Vector 
{
public:
    Vector();
    Vector(std::initializer_list<T> init);
    ~Vector();

    void push_back(const T& value);
    void pop_back();
    void push_front(const T& value);
    void pop_front();
    void insert(std::size_t index, const T& value);

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    std::size_t size() const;
    bool empty() const;

private:
    void resize(std::size_t new_size);
    void reserve(std::size_t new_capacity);

private:
    void reallocate(std::size_t new_capacity);


    T* data;
    std::size_t capacity;
    std::size_t count;
};

template<typename T>
Vector<T>::Vector() : data(nullptr), capacity(0), count(0) {}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> init) : data(nullptr), capacity(0), count(0) 
{
    for (const T& value : init) 
    {
        push_back(value);
    }
}

template<typename T>
Vector<T>::~Vector() 
{
    delete[] data;
}

template<typename T>
void Vector<T>::push_back(const T& value) 
{
    if (count == capacity) 
    {
        resize();
    }
    data[count++] = value;
}

template<typename T>
void Vector<T>::pop_back() 
{
    if (count == 0) 
    {
        std::cerr << "Vector is empty" << std::endl;
        return;
    }
    --count;
}

template<typename T>
void Vector<T>::push_front(const T& value) 
{
    if (count == capacity) 
    {
        resize();
    }
    for (std::size_t i = count; i > 0; --i) 
    {
        data[i] = data[i - 1];
    }
    data[0] = value;
    ++count;
}

template<typename T>
void Vector<T>::pop_front() 
{
    if (count == 0) 
    {
        std::cerr << "Vector is empty" << std::endl;
        return;
    }
    for (std::size_t i = 0; i < count - 1; ++i) 
    {
        data[i] = data[i + 1];
    }
    --count;
}

template<typename T>
void Vector<T>::insert(std::size_t index, const T& value) 
{
    if (index > count) 
    {
        std::cerr << "Index out of range" << std::endl;
    }
    if (count == capacity) 
    {
        resize();
    }
    for (std::size_t i = count; i > index; --i) 
    {
        data[i] = data[i - 1];
    }
    data[index] = value;
    ++count;
}

template<typename T>
T& Vector<T>::operator[](std::size_t index) 
{
    if (index >= count) 
    {
        std::cerr << "Index out of range" << std::endl;
        exit(1);
    }
    return data[index];
}

template<typename T>
const T& Vector<T>::operator[](std::size_t index) const 
{
    if (index >= count) 
    {
        std::cerr << "Vector is empty" << std::endl;
        return 1;
    }
    return data[index];
}

template<typename T>
std::size_t Vector<T>::size() const 
{
    return count;
}

template<typename T>
bool Vector<T>::empty() const 
{
    return count == 0;
}

template<typename T>
void Vector<T>::reserve(std::size_t new_capacity) 
{
    if (new_capacity > capacity) 
    {
        reallocate(new_capacity);
    }
}

template<typename T>
void Vector<T>::resize(std::size_t new_size) 
{
    std::size_t new_capacity = capacity == 0 ? 1 : 2 * capacity;
    T* new_data = new T[new_capacity];
    for (std::size_t i = 0; i < count; ++i) 
    {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}
}
int main() {
    myVec::Vector<int> vec = {1, 2, 3};

    vec.push_back(4);
    vec.push_front(0);
    vec.insert(2, 99);
    vec.pop_back();
    vec.pop_front();

    for (std::size_t i = 0; i < vec.size(); ++i) 
    {
        std::cout << vec[i] << ' ';
    }
    std::cout << std::endl;

    return 0;
}
