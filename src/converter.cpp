#include<iostream>
#include"converter.hpp"


Converter::Converter() 
{
    CharList _input {};
    CharList _output {};
    
    _invalid_expression = false;
    _recursive_call_counter = 0;
    _reversed_output = false;

    _operands_count = 0;
    _operators_count = 0;
    _trivial_char_count = 0;
    
}


Converter::~Converter()
{
    _input.~CharList();
    _output.~CharList();
}

/// @brief adds a character to the end of the list of characters recieved
/// @param c a character value
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
    
    // c is an invalid character or whitespace
    else
    {
        _trivial_char_count++;
    }
    _input.pushc(c);
}

/// @brief This method recursively converts a prefix expression by finding 
/// the next two operands for each operator.
/// @param op an Operand struct
/// @return an Operand struct with the next operand stored in the expression
/// field and a pointer to the next character in the expression in the next
/// field.
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
        
        // Left operand found
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
        
        // right operand found
        Operand right_operand = find_next_operand(right_op);

        // concatenate left_operand + right_operand + operator and return
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

/// @brief This method converts the stored prefix expression to its
/// associated postfix expression and stores the result internally.
void Converter::convert_expression()
{
    // If the input is exclusively whitespace
    if (_input.size() == _trivial_char_count)
    {
        return;
    }
    
    // A candidate expression must have satisfy:
    // Total number of Operands = total number of operators + 1
    if (_operands_count != (_operators_count + 1))
    {
        _invalid_expression = true;
        return;
    }
    Node* first = _input.get_head();
    CharList expression {};
    Operand operand {expression, first};
    
    // begin recursive calls
    Operand converted_expression = find_next_operand(operand);
    _output = converted_expression.expression;
    
    // This check may be unnecessary, but leaving as final check
    if (_output.size() != (_operands_count + _operators_count))
    {
        _invalid_expression = true;
    }
}


/// @brief Toggles whether or not the provided expressions are reversed
/// when displayed to output
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

    if (conv._invalid_expression)
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

/// @brief Resets converter to default state
void Converter::reset()
{
    CharList new_input {};
    _input = new_input; // copy assignment
    _output = new_input; // copy assignment
    
    _invalid_expression = false;
    _reversed_output = false;
    _recursive_call_counter = 0;

    _operands_count = 0;
    _operators_count = 0;
    _trivial_char_count = 0;
}

