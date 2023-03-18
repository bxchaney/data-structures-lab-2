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

        CharList _input;
        CharList _output;

        bool _illegal_characters;
        bool _invalid_expression;
        int _recursive_call_counter;
        bool _reversed_output;

        int _operands_count;
        int _operators_count;
        int _whitespace_count;

        // Recursive method
        Operand find_next_operand(Operand&);
        bool is_only_whitespace();
        bool is_candidate_expression();
        
    public:

        Converter();
        ~Converter();

        void pushc(char);
        void convert_expression();
        bool has_illegal_character();
        bool is_invalid_expression();

        void reverse_output();
        friend std::ostream& operator<<(std::ostream&, const Converter&);
        
        void reset();
        int recursive_call_total();

};