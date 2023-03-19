#include<iostream>
#include<fstream>
#include"char_list.hpp"
#include"converter.hpp"



int main(int argc, char** argv) 
{

    if (argc < 3)
    {
        std::cout << "Please provide the input and output files."; 
        std::cout << std::endl;
        return -1;
    }


    std::filebuf fb_input;
    std::filebuf fb_output;
    if (!fb_input.open(argv[1], std::ios::in))
    {
       std::cout << "Problem opening input file!" << std::endl;
       return -1;
    }
    else if (!fb_output.open(argv[2], std::ios::out))
    {
        std::cout << "Problem opening output file!" << std::endl;
        fb_input.close();
        return -1;
    }

    std::istream is(&fb_input);
    std::ostream os(&fb_output);
    char c;
    Converter converter {};
    while(( c = is.get()) != -1)
    {
        if (c == 13)
        {
            continue;
        }
        if (c == 10) // newline
        {
            converter.convert_expression();
            std::cout << converter;
            os << converter;
            converter.reset();
        }
        else
        {
            converter.pushc(c);
        }
    }
    
    fb_input.close();
    fb_output.close();
    
}