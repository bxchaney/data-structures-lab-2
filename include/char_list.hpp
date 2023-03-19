#pragma once
#include<iostream>

struct Node 
{
    char character;
    Node* prev;
    Node* next;
};

class CharList
{  
    private:

        int _size;
        Node* _head;
        Node* _tail;
        bool _reverse_string;
        
    public:
        
        CharList();
        CharList(const CharList&);
        ~CharList();

        void operator = (const CharList&);
        
        void pushc(char);
        char pop();
        void append(CharList&);    
        friend std::ostream& operator<<(std::ostream&, const CharList&);
        int size();
        void reverse();

        Node* get_head();

};