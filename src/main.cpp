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

/// @brief This function reads postfix expressions character by character from
/// the input stream and writes output to the output stream and the console.
/// This function assumes that postfix expressions are delimted by newline
/// characters in the input stream.
/// @param is an input stream containing newline-delimited postfix expressions
/// @param os an output stream that is not std::cout
/// @param conv an initialized Converter
void postfix_to_prefix(std::istream& is, std::ostream& os, Converter& conv)
{
    // Converter is only configured to convert from Prefix -> Postfix
    // this method reads each line, then pushes the characters in reverse to
    // the Converter and reverses the Converter's output.
    char c;
    CharList cl {};
    // Repeat until EOF
    while(( c = is.get()) != EOF)
    {
        if (c == 13) // ignoring carriage returns
        {
            continue;
        }
        if (c == 10) // newline
        {
            // Push each character from the line in LIFO order to
            // the converter
            while(cl.size())
            {
                conv.pushc(cl.pop());
            }
            
            // convert and write output
            conv.convert_expression();
            conv.reverse_output();
            std::cout << conv;
            os << conv;
            conv.reset();
        }
        
        // push non-newline, non-carriage returns to cl
        else
        {
            cl.pushc(c);
        }
    }
}

/// @brief This function reads prefix expressions character by character from
/// the input stream and writes output to the output stream and the console.
/// This function assumes that prefix expressions are delimted by newline
/// characters in the input stream.
/// @param is an input stream containing newline-delimited prefix expressions
/// @param os an output stream that is not std::cout
/// @param conv an initialized Converter
void prefix_to_postfix(std::istream& is, std::ostream& os, Converter& conv)
{
    char c;
    while(( c = is.get()) != -1)
    {
        if (c == 13) // ignore carriage returns
        {
            continue;
        }
        if (c == 10) // newline
        {
            // convert expression and write to output
            conv.convert_expression();
            std::cout << conv;
            os << conv;
            conv.reset();
        }
        
        // push non-newline, non-carraige returns to conv
        else
        {
            conv.pushc(c);
        }
    }
}

int main(int argc, char** argv) 
{
    // not enough arguments provided
    if (argc < 3)
    {
        std::cout << "Please provide the input and output files."; 
        std::cout << std::endl;
        return -1;
    }


    std::filebuf fb_input;
    std::filebuf fb_output;
    
    // confirming input can open
    if (!fb_input.open(argv[1], std::ios::in))
    {
       std::cout << "Problem opening input file!" << std::endl;
       return -1;
    }
    
    // confirming output can open
    else if (!fb_output.open(argv[2], std::ios::out))
    {
        std::cout << "Problem opening output file!" << std::endl;
        fb_input.close();
        return -1;
    }


    std::istream is(&fb_input);
    std::ostream os(&fb_output);
    Converter converter {};
    
    // If 4 or more command line args, searching for -r flag
    if (argc >= 4)
    {
        // confirming -r flag is present
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
    // Otherwise, attempting prefix -> postfix conversion
    else
    {
        prefix_to_postfix(is, os, converter);
    }
       
    fb_input.close();
    fb_output.close();
    return 0;
}