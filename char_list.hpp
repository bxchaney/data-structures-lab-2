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
        
        void pushc(char);
        void append(CharList&);    
        friend std::ostream& operator<<(std::ostream&, const CharList&);
        int size();
        void reverse();

        Node* get_head();
        Node* get_tail();

        void set_head(Node*);
        void set_tail(Node*);
};