#include<iostream>
#include"converter.hpp"


Converter::Converter() 
{
    CharList _input {};
    CharList _output {};
    
    _illegal_characters = false;
    _invalid_expression = false;
    _recursive_call_counter = 0;
    _reversed_output = false;

    _operands_count = 0;
    _operators_count = 0;
    _whitespace_count = 0;
    
}


Converter::~Converter()
{
    _input.~CharList();
    _output.~CharList();
}

void Converter::pushc(char c)
{
    // c is a valid character if it is an accepted operand or an accepted
    // operator. Otherwise, it is an illegal character. All characters are
    // pushed to input, only non-whitespace, legal characters will be shown
    // in the final output.

    // c is an operator
    if ( 
            c == '+' 
            || c == '-' 
            || c == '*' 
            || c == '/' 
            || c == '$' 
            || c == '^'
            || c == '%'
        )
    {
        _operators_count++;
    }
    
    // c is an operand
    else if (
                ('0' <= c && c <= '9') 
                || ('A' <= c && c <= 'Z') 
                || ('a' <= c && c <= 'z')
            )
    {
        _operands_count++;
    }
    
    // c is a space or tab
    else if (
                c == ' ' // space
                || c == '\t' // tab
            )
    {
        _whitespace_count++;
    }
    
    // c is invalid character
    else
    {
        _illegal_characters = true;
    }
    _input.pushc(c);
}

Converter::Operand Converter::find_next_operand(Operand& op)
{
    CharList expression {};
    _recursive_call_counter++;
    if (op.node == nullptr) { return Operand{op.expression, nullptr};}
    char c = (op.node->character);       
    // if c is an operand, return it
    if (
        ('0' <= c && c <= '9') 
        || ('A' <= c && c <= 'Z') 
        || ('a' <= c && c <= 'z')
       )
    {
        expression.pushc(c);
        return Operand{expression, op.node->next};
    }
    
    // If c is an operator, find left and right operands
    if (
        c == '+' 
        || c == '-' 
        || c == '*' 
        || c == '/' 
        || c == '$' 
        || c == '^'
        || c == '%'
       )
    {
        Node* next = op.node->next;
        Operand operand {expression, next};
        Operand left_operand = find_next_operand(operand);
        next = left_operand.node;
        if (next == nullptr) 
        { 
            _invalid_expression = true;
            left_operand.expression.pushc(c);
            return Operand{left_operand.expression, nullptr};
        }
        
        CharList right_expression {};
        Operand right_op {right_expression, next };
        Operand right_operand = find_next_operand(right_op);

        left_operand.expression.append(right_operand.expression);
        left_operand.expression.pushc(c);
        Operand new_operand = Operand{
                                left_operand.expression,right_operand.node
                                };
        return new_operand;
    }

    // If c is tab, space, or illegal character return the next character
    else 
    {
        
        Operand operand {expression, op.node->next};
        return find_next_operand(operand);
    }

}

bool Converter::is_only_whitespace()
{
    return (_input.size() == _whitespace_count);
}

bool Converter::is_candidate_expression()
{
    // A check that the total number of operands is 1 greater than the total
    // number of operators
    return (_operands_count == (_operators_count + 1));
}

void Converter::convert_expression()
{
    if (is_only_whitespace())
    {
        return;
    }
    if (!is_candidate_expression())
    {
        
        _invalid_expression = true;
        return;
    }
    Node* first = _input.get_head();
    CharList expression {};
    Operand operand {expression, first};
    Operand converted_expression = find_next_operand(operand);
    _output = converted_expression.expression;
    
    // This check may be unnecessary, but leaving as final check
    if (_output.size() != (_operands_count + _operators_count))
    {
        _invalid_expression = true;
    }
}

bool Converter::has_illegal_character()
{
    return _illegal_characters;
}

bool Converter::is_invalid_expression()
{
    return _invalid_expression;
}

void Converter::reverse_output()
{
    _input.reverse();
    _output.reverse();
}

std::ostream& operator<<(std::ostream& os, const Converter& conv)
{
    os << "Input: " << conv._input << std::endl;
    os << "Recursive Calls: " << conv._recursive_call_counter << std::endl;
    os << "Output: ";
    if (conv._illegal_characters)
    {
        os << "This expression has illegal characters." << std::endl;
    }
    else if (conv._invalid_expression)
    {
        os << "This is an invalid expression" << std::endl;
    }
    else 
    {
        os << conv._output << std::endl;
    }
    os << std::endl;
    return os;
}

void Converter::reset()
{
    CharList new_input {};
    _input = new_input; // copy assignment
    _output = new_input; // copy assignment
    
    _illegal_characters = false;
    _invalid_expression = false;
    _reversed_output = false;
    _recursive_call_counter = 0;

    _operands_count = 0;
    _operators_count = 0;
    _whitespace_count = 0;
}

int Converter::recursive_call_total()
{
    return _recursive_call_counter;
}
