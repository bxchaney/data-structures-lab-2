/**
 * Converter holds the algorithm for converting each expression and con be
 * written to an ostream as formatted output. To aid the recursive method
 * of parsign each expression, Converter makes use of a private struct Operand
 * which has a CharList field expression, and a Node* field next. This struct
 * is the input and return type of the private member function
 * find_next_operand. 
 * 
 * The algorithm works as follows:
 * 
 *  - First confirm that we have a non-trival input. This would be an input
 *  that is not exclusively whitespace or illegal characters.
 *  
 *  - Then, confirm that the non-trival input is a candidate expression. A
 *  valid prefix or postfix expressions must satisfy the condition that total
 *  number of operand characters is equal to 1 greater than the total number
 *  of operator characters. This allows us to immediately exclude expressions
 *  like 'AA' or '++AB'
 * 
 *  - Once these edge cases are handled, then we can recursively parse the
 *  expression. Our recursive base case is when we encounter a single letter
 *  operand. When we encounter an operator, we recursively call 
 *  find_next_operand to find the left operand of the operator. We then call
 *  find_next_operand again to find the right operand of the operator. We 
 *  then concatenate left operand + right operand + operator and return it
 *  with a reference to the next character.
 * 
 * - When find_next_operand finishes, we have to confirm that the output has
 * the expected number of operators and operands. Expressions like 'B+A' or 
 * '+AB-C' would pass our initial check to confirm candidacy, but would return
 * 'B' and 'AB+' respectively. This final check confirms we catch all invalid
 * expressions.
 * 
 * Converter supports the following public interface:
 * 
 * void pushc(char):
 *  
 *      Input: A character
 * 
 *      Precondition: Converter is initialized
 * 
 *      Process: Converter pushes the character to the input CharList. If it
 *          is whitespace, and operator, or an operand, then the respective
 *          counter is incremented by 1. Otherwise, the illegal character
 *          flag is set to true.
 * 
 *      Postcondition: the character is stored at the end of the input CharList
 * 
 *      Output: None
 * 
 * void convert_expression():
 * 
 *      Input: None
 * 
 *      Precondition: Converter is initialized
 * 
 *      Process: confirms the input expression is a candidate expression and
 *          begins the recursive calls to convert the expression.
 * 
 *      Postcondition: Either the converted expression is now stored in output
 *          or the appropriate error flags are set to true.
 * 
 *      Output: None
 * 
 * void reverse_output():
 * 
 *      Input: None
 * 
 *      Precondition: Converter is initialized
 * 
 *      Process: Toggles whether the input and output CharLists will return
 *          reversed strings.
 * 
 *      Postcondition: CharList now output reversed characters
 * 
 *      Output: None
 * 
 * void reset():
 * 
 *      Input: None
 * 
 *      Precondition: None
 * 
 *      Process: Resets Converter to default state.
 * 
 *      Postcondition: Converter is in same state as when first initialized
 * 
 *      Output: None
 * 
 * 
 */

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
        
    public:

        Converter();
        ~Converter();

        void pushc(char);
        void convert_expression();
        void reverse_output();
        void reset();
        
        friend std::ostream& operator<<(std::ostream&, const Converter&);
};