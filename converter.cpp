#pragma once
#include<iostream>
#include"converter.hpp"


// Converter::Operand::~Operand()
// {
    
//     node = nullptr;
// }

Converter::Converter() 
{
    CharList _input {};
    _illegal_characters = false;
    _invalid_expression = false;
    _recursive_call_counter = 0;
    CharList _output {};
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
    if (
        !( 
            ( 
                c == '+' 
                || c == '-' 
                || c == '*' 
                || c == '/' 
                || c == '$' 
                || c == '^'
                || c == '%'
            ) 
            || 
            (
                ('0' <= c && c <= '9') 
                || ('A' <= c && c <= 'Z') 
                || ('a' <= c && c <= 'z')
            )
            ||
            (
                c == 20 // space
                || c == 9 // tab
            )
        )
       )
    {
        _illegal_characters = true;
    }
    _input.pushc(c);
}

Converter::Operand Converter::find_next_operand(Operand& op)
{
    CharList expression{};
    _recursive_call_counter++;
    if (op.node == nullptr) { return Operand{op.expression, nullptr};}
    char c = (op.node->character);       
    std::cout << "character is:" << c << std::endl; 
    // if c is an operand, return it
    if (
        ('0' <= c && c <= '9') 
        || ('A' <= c && c <= 'Z') 
        || ('a' <= c && c <= 'z')
       )
    {
        // CharList expression {};
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
        Operand left_operand = find_next_operand(Operand{expression, next});
        next = left_operand.node;
        if (next == nullptr) 
        { 
            _invalid_expression = true;
            left_operand.expression.pushc(c);
            return Operand{left_operand.expression, nullptr};
        }
        Operand* right_operand = find_next_operand(new Operand{nullptr, next});

        // right_operand's expression field is a hanging pointer after this
        // operation.
        left_operand->expression->append(right_operand->expression);
        left_operand->expression->pushc(c);
        Operand* new_operand = new Operand{
                                        left_operand->expression,
                                        right_operand->node
                                    };
        
        
        delete left_operand;
        delete right_operand;
        return new_operand;
    }

    // If c is tab, space, or illegal character return the next character
    else 
    {
        
        return find_next_operand(new Operand{nullptr, op->node->next});
    }

}

void Converter::convert_expression()
{
    Node* first = _input.get_head();
    Operand* converted_expression = find_next_operand(new Operand{nullptr, first});
    if (_output != nullptr)
    {
        delete _output;
    }
    _output = converted_expression->expression;
}

bool Converter::has_illegal_character()
{
    return _illegal_characters;
}

bool Converter::is_invalid_expression()
{
    return _invalid_expression;
}

const char* Converter::get_output()
{
    if (_output == nullptr) return "";
    return _output->get_contents();
}

const char* Converter::get_output_reversed()
{
    if (_output == nullptr) return "";
    return _output->get_contents_reversed();
}

void Converter::reset()
{
    delete _input;
    if (_output != nullptr) { delete  _output;}

    _input = new CharList();
    _illegal_characters = false;
    _invalid_expression = false;
    _recursive_call_counter = 0;
    _output = nullptr; 
}

int Converter::recursive_call_total()
{
    return _recursive_call_counter;
}
