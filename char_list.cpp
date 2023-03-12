#include<iostream>
#include"char_list.hpp"


CharList::CharList()
{
    _size = 0;
    _head = nullptr;
    _tail = nullptr;
}

CharList::~CharList()
{
    std::cout << "CharList Destructor called" << std::endl;
    // If list is not empty
    while (_head != nullptr)
    {
        Node* current_node = _head;
        _head = _head->next;

        current_node->prev = nullptr;
        current_node->next = nullptr;
        delete current_node;
    }
    _tail = nullptr;
}

void CharList::pushc(char c)
{
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

void CharList::append(CharList& list)
{  
    Node* new_node = list.get_head();

    while (new_node != nullptr)
    {
        pushc(new_node->character);
        new_node = new_node->next;
    }
}

const char* CharList::get_contents()
{
    if (_size == 0) return "";

    char* str = new char[_size];

    Node* current_node = _head;

    for (int i = 0; current_node != nullptr; i++)
    {
        str[i] = current_node->character;
        current_node = current_node->next;
    }

    return str;
}

const char* CharList::get_contents_reversed()
{
    if (_size == 0) return "";

    char* str = new char[_size];

    Node* current_node = _tail;

    for (int i = 0; current_node != nullptr; i++)
    {
        str[i] = current_node->character;
        current_node = current_node->prev;
    }

    return str;
}

int CharList::size()
{
    return _size;
}

Node* CharList::get_head()
{
    return _head;
}

Node* CharList::get_tail()
{
    return _tail;
}

void CharList::set_head(Node* node)
{
    _head = node;
}

void CharList::set_tail(Node* node)
{
    _tail = node;
}
