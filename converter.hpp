#pragma once
#include<iostream>
#include"char_list.hpp"

class Converter
{
    private:
        struct Operand 
        {
            CharList expression;
            Node* node;
        };
        
        // Recursive method
        Operand find_next_operand(Operand&);

        CharList _input;
        CharList _output;

        bool _illegal_characters;
        bool _invalid_expression;
        int _recursive_call_counter;
        bool _reversed_output;

    public:

        Converter();
        ~Converter();

        void pushc(char);
        void convert_expression();
        bool has_illegal_character();
        bool is_invalid_expression();

        void reverse_output();
        friend std::ostream& operator<<(std::ostream&, const Converter&);
        
        // const char* get_output();
        // const char* get_output_reversed();

        void reset();
        int recursive_call_total();

};