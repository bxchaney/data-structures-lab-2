/**
 * The CharList is a doubly-linked list implementation of a stack-like string,
 * supporting the push and pop methods. Additionally, this data structure
 * supports an append method which copies the contents of another CharList to
 * the top end of this string. This implementation was used because it can be
 * recursively traversed; every node has a next field containing a reference
 * to the next node or a null pointer. Although a singly linked list could be
 * used in the same manner, the doubly linked implementation allows us to
 * traverse the string in reverse as well, enabling this program to process
 * Postfix expressions as well as prefix expressions.
 * 
 * CharList supports the following public interface:
 * 
 * void pushc(char):
 *     
 *      Input: a character.
 * 
 *      Precondition: CharList is initialized.
 * 
 *      Process: CharList dynamically creates a new Node and appends it to the
 *          end of the string.
 * 
 *      Postcondition: The size of CharList is incremented by 1.
 * 
 *      Output: None
 * 
 * 
 * char pop():
 * 
 *      Input: None
 * 
 *      Precondition: CharList is non-empty.
 * 
 *      Process: The last Node is removed and its char value is returned.
 * 
 *      Postcondition: The size fo CharList is decremented by 1.
 * 
 *      Output: The character previously at the end of the string. If the
 *          string was empty then the null character is returned.
 * 
 * 
 * void append(CharList&):
 * 
 *      Input: a reference to another CharList object.
 * 
 *      Precondition: CharList and the references CharList are initialized.
 * 
 *      Process: The contents of the referenced CharList are pushed to
 *          CharList in the order they were added to the referenced CharList.
 * 
 *      PostCondition: None
 * 
 *      Output: None
 * 
 * 
 * int size():
 * 
 *      Input: None
 * 
 *      Precondition: None
 * 
 *      Process: Returns the value of the member variable used for tracking
 *          size.
 * 
 *      Postcondition: None
 * 
 *      Output: The number of characters stored in CharList.
 * 
 * 
 * void reverse():
 * 
 *      Input: None
 * 
 *      Precondition: None
 * 
 *      Process: Toggles a boolean flag indicating whether the CharList
 *          goes to output in reverse or not.
 * 
 *      Postcondition: the reverse flag is toggled.
 * 
 *      Output: None
 * 
 * 
 * Node* get_head()
 * 
 *      Input: None
 * 
 *      Precondition: None
 * 
 *      Process: Returns pointer to the head Node in CharList.
 * 
 *      Postcondition: This gives the user read/write access to essentially
 *          any element in the CharList.
 * 
 *      Output: a Node* pointer to the first element of CharList.
 * 
 */

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