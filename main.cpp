#include<iostream>
#include"char_list.cpp"
#include"converter.cpp"



int main() 
{

    CharList a {};

    a.pushc('a');
    a.pushc('b');
    a.pushc('c');
    a.pushc('d');

    CharList b {};

    b.pushc('e');
    b.pushc('f');
    b.pushc('g');
    b.pushc('h');

    a.append(b);

    std::cout << a << std::endl;

    a.reverse();

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    



    Converter converter {};

    converter.pushc('+');
    converter.pushc('-');
    converter.pushc('A');
    // converter.pushc(' ');
    converter.pushc('B');
    converter.pushc('*');
    converter.pushc('C');
    converter.pushc('D');

    std::cout << "values pushed" << std::endl;

    converter.convert_expression();

    std::cout << converter << std::endl;

    // std::cout << converter.is_invalid_expression() << std::endl;


}