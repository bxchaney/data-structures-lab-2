#pragma once

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
        
    public:
        
        CharList();
        ~CharList();
        
        void pushc(char);
        void append(CharList&);    
        const char* get_contents();
        const char* get_contents_reversed();
        int size();

        Node* get_head();
        Node* get_tail();

        void set_head(Node*);
        void set_tail(Node*);
};