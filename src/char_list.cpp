#include<iostream>
#include"char_list.hpp"


CharList::CharList()
{
    _size = 0;
    _head = nullptr;
    _tail = nullptr;
    _reverse_string = false;
}

// The copy constructor for CharList
CharList::CharList(const CharList& cl)
{

    // same assignments as regular constructor
    _size = 0;
    _head = nullptr;
    _tail = nullptr;

    // use same reverse flag as copy source
    _reverse_string = cl._reverse_string;
    Node* current_node = cl._head;
    
    // push each char in cl to the copy
    while (current_node != nullptr)
    {
        pushc(current_node->character);
        current_node = current_node->next;
    }
}

CharList::~CharList()
{
    // If list is not empty
    while (_head != nullptr)
    {
        // iteratively deleted nodes
        Node* current_node = _head;
        _head = _head->next;

        delete current_node;
    }
    _tail = nullptr;
}

void CharList::operator = (const CharList& cl)
{
    // same copy code as the copy constructor
    _size = 0;
    _head = nullptr;
    _tail = nullptr;
    _reverse_string = cl._reverse_string;
    Node* current_node = cl._head;
    while (current_node != nullptr)
    {
        pushc(current_node->character);
        current_node = current_node->next;
    }
}

/// @brief This method appends a character to the end of CharList
/// @param c a character value
void CharList::pushc(char c)
{
    // allocating new Node on heap
    Node* new_node = new Node{c, nullptr, nullptr};

    // List is empty
    if (_head == nullptr)
    {
        _head = new_node;
        _tail = new_node;
    }
    else 
    {
        new_node->prev = _tail;
        _tail->next = new_node;
        _tail = new_node;
    }
    _size++;
}

/// @brief This method returns and removes the character value of the node at
/// the end of CharList.
/// @return the character at the end of CharList. If CharList is empty when
/// this method is called, returns the null character.
char CharList::pop()
{
    if (_size == 0)
    {
        return '\0'; // null character
    }
    
    char c;
    // edge case when popping last element
    if (_size == 1)
    {
        c = _head->character;
        delete _head;
        _head = nullptr;
        _tail = nullptr;
        
    }
    else
    {
        Node* prev_node = _tail->prev;
        prev_node->next = nullptr;
        c = _tail->character;

        delete _tail;
        _tail = prev_node;
    }
    _size--;
    return c;
}

/// @brief This method copies another CharList's contents to the end of
/// a CharList
/// @param list the CharList whose contents are being copied.
void CharList::append(CharList& list)
{  
    Node* new_node = list._head;

    while (new_node != nullptr)
    {
        pushc(new_node->character);
        new_node = new_node->next;
    }
}



/// @brief overloading the << operator to stream character values directly
/// to output. If the CharList is reversed, returns characters LIFO. By 
/// default returns characters FIFO.
/// @param os an output stream, could be writing to a file or console.
/// @param cl this CharList
/// @return an ostream containing the contents of CharList
std::ostream& operator<<(std::ostream& os, const CharList& cl)
{
    Node* current_node;
    
    // If reversed, read from tail forwards.
    if (cl._reverse_string)
    {
        current_node = cl._tail;
        while (current_node != nullptr)
        {
            os << current_node->character;
            current_node = current_node->prev;
        }
    }
    
    // otherwise, read from head, backwards.
    else
    {
        current_node = cl._head;
        while (current_node != nullptr)
        {
            os << current_node->character;
            current_node = current_node->next;
        }
    }
    return os;
}

/// @brief The current number of characters in CharList
/// @return the numeber of characters in CharList
int CharList::size()
{
    return _size;
}

/// @brief This method toggles CharList's reverse flag.
void CharList::reverse()
{
    _reverse_string = !_reverse_string;
}

/// @brief This method returns a pointer to the head node of CharList
/// @return the head node of CharList
Node* CharList::get_head()
{
    return _head;
}

