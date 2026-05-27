#include "PriorityQueue.h"
#include <sstream>
#include <stdexcept>

PriorityQueue::PriorityQueue() : m_elements(nullptr), m_count(0) {}

PriorityQueue::PriorityQueue(const std::initializer_list<int>& items) 
    : m_elements(nullptr), m_count(items.size())
{
    if (m_count > 0)
    {
        m_elements = new int[m_count];
        size_t idx = 0;
        for (const int& val : items)
        {
            m_elements[idx++] = val;
        }

        for (size_t i = 0; i < m_count - 1; ++i)
        {
            for (size_t j = 0; j < m_count - i - 1; ++j)
            {
                if (m_elements[j] > m_elements[j + 1])
                {
                    int temp = m_elements[j];
                    m_elements[j] = m_elements[j + 1];
                    m_elements[j + 1] = temp;
                }
            }
        }
    }
}

PriorityQueue::PriorityQueue(const PriorityQueue& other) 
    : m_elements(nullptr), m_count(other.m_count)
{
    if (m_count > 0)
    {
        m_elements = new int[m_count];
        for (size_t i = 0; i < m_count; ++i)
        {
            m_elements[i] = other.m_elements[i];
        }
    }
}

PriorityQueue::PriorityQueue(PriorityQueue&& other) noexcept 
    : m_elements(other.m_elements), m_count(other.m_count)
{
    other.m_elements = nullptr;
    other.m_count = 0;
}

PriorityQueue::~PriorityQueue()
{
    delete[] m_elements;
}

std::string PriorityQueue::to_string() const
{
    if (is_empty())
    {
        return "Empty";
    }

    std::stringstream ss;
    for (size_t i = 0; i < m_count; ++i)
    {
        ss << m_elements[i];
        if (i < m_count - 1)
        {
            ss << " ";
        }
    }
    return ss.str();
}

size_t PriorityQueue::get_size() const
{
    return m_count;
}

bool PriorityQueue::is_empty() const
{
    return m_count == 0;
}

void PriorityQueue::insert(const int value)
{
    int* tempArray = new int[m_count + 1];
    size_t i = 0;
    
    while (i < m_count && m_elements[i] < value)
    {
        tempArray[i] = m_elements[i];
        i++;
    }
    
    tempArray[i] = value;
    
    while (i < m_count)
    {
        tempArray[i + 1] = m_elements[i];
        i++;
    }

    delete[] m_elements;
    m_elements = tempArray;
    m_count++;
}

void PriorityQueue::remove_max()
{
    if (is_empty())
    {
        throw std::out_of_range("Очередь пуста!");
    }

    int* tempArray = (m_count > 1) ? new int[m_count - 1] : nullptr;
    for (size_t i = 0; i < m_count - 1; ++i)
    {
        tempArray[i] = m_elements[i];
    }

    delete[] m_elements;
    m_elements = tempArray;
    m_count--;
}

int PriorityQueue::get_max() const
{
    if (is_empty())
    {
        throw std::out_of_range("Очередь пуста!");
    }
    return m_elements[m_count - 1];
}

int PriorityQueue::get_min() const
{
    if (is_empty())
    {
        throw std::out_of_range("Очередь пуста!");
    }
    return m_elements[0];
}

PriorityQueue& PriorityQueue::operator=(const PriorityQueue& other)
{
    if (this != &other)
    {
        delete[] m_elements;
        m_count = other.m_count;
        m_elements = (m_count > 0) ? new int[m_count] : nullptr;
        for (size_t i = 0; i < m_count; ++i)
        {
            m_elements[i] = other.m_elements[i];
        }
    }
    return *this;
}

PriorityQueue& PriorityQueue::operator=(PriorityQueue&& other) noexcept
{
    if (this != &other)
    {
        delete[] m_elements;
        m_elements = other.m_elements;
        m_count = other.m_count;
        
        other.m_elements = nullptr;
        other.m_count = 0;
    }
    return *this;
}

PriorityQueue& PriorityQueue::operator<<(int value)
{
    insert(value);
    return *this;
}

PriorityQueue& PriorityQueue::operator>>(int& value)
{
    value = get_max();
    remove_max();
    return *this;
}