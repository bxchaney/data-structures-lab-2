#include<iostream>
#include"char_list.hpp"


CharList::CharList()
{
    _size = 0;
    _head = nullptr;
    _tail = nullptr;
    _reverse_string = false;
}

CharList::CharList(const CharList& cl)
{
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

CharList::~CharList()
{
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

void CharList::operator = (const CharList& cl)
{
    _size = 0;
    _reverse_string = cl._reverse_string;
    _head = nullptr;
    _tail = nullptr;
    Node* current_node = cl._head;
    while (current_node != nullptr)
    {
        pushc(current_node->character);
        current_node = current_node->next;
    }
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

char CharList::pop()
{
    if (_size == 0)
    {
        return '\0';
    }

    Node* prev_node = _tail->prev;
    prev_node->next = nullptr;
    char c = _tail->character;
    _tail->next = nullptr;
    _tail->prev = nullptr;

    delete _tail;
    _tail = prev_node;

    _size--;
    return c;
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

std::ostream& operator<<(std::ostream& os, const CharList& cl)
{
    Node* current_node;
    if (cl._reverse_string)
    {
        current_node = cl._tail;
        while (current_node != nullptr)
        {
            os << current_node->character;
            current_node = current_node->prev;
        }
    }
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

int CharList::size()
{
    return _size;
}

void CharList::reverse()
{
    _reverse_string = !_reverse_string;
}

Node* CharList::get_head()
{
    return _head;
}

Node* CharList::get_tail()
{
    return _tail;
}

