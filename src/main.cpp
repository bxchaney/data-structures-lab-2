#include<iostream>
#include<fstream>
#include"char_list.hpp"
#include"converter.hpp"

/// @brief This fucntion is used for string comparisons while parsing
/// command line inputs.
/// @param s a character pointer to an entry from argv
/// @param str a character array that s is being compared against
/// @return a boolean indicating where s and str represent equivalent
/// character arrays.
bool is_equal_str(char* s, const char* str)
{
    
    for (int i=0; ;i++)
    {
        // If one of s or str has terminated but the other has not,
        // return false.
        if ((!s[i] && str[i]) || (!str[i] && s[i]))
        {
            return false;
        } 
        // Otherwise, if one has terminated (meaning the other has also
        // terminated at the same index) return true.
        else if (!s[i]) 
        {
            return true;
        }
        // If the character arrays have different values at any indeces,
        // return false.
        if (s[i] != str[i]) return false;
    }
}

void postfix_to_prefix(std::istream& is, std::ostream& os, Converter& conv)
{
    char c;
    CharList cl {};
    while(( c = is.get()) != -1)
    {
        if (c == 13)
        {
            continue;
        }
        if (c == 10) // newline
        {
            while(cl.size())
            {
                conv.pushc(cl.pop());
            }
            conv.convert_expression();
            conv.reverse_output();
            std::cout << conv;
            os << conv;
            conv.reset();
        }
        else
        {
            cl.pushc(c);
        }
    }
}

void prefix_to_postfix(std::istream& is, std::ostream& os, Converter& conv)
{
    char c;
    while(( c = is.get()) != -1)
    {
        if (c == 13)
        {
            continue;
        }
        if (c == 10) // newline
        {
            conv.convert_expression();
            std::cout << conv;
            os << conv;
            conv.reset();
        }
        else
        {
            conv.pushc(c);
        }
    }
}

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
    Converter converter {};
    if (argc >= 4)
    {
        if (is_equal_str(argv[3], "-r"))
        {
            postfix_to_prefix(is, os, converter);
        }
        else
        {
            std::cout << "Could not determine if prefix to postfix or vice ";
            std::cout << "versa is requested. If providing a 4th command line";
            std::cout << " please ensure it is '-r' to enable postfix to prefix";
            std::cout << " conversion." << std::endl;
        }

    }
    else
    {
        prefix_to_postfix(is, os, converter);
    }
       
    fb_input.close();
    fb_output.close();
    
}