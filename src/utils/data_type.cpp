#include <iostream>
#include <string>
#include <algorithm>

namespace DataType
{
    // Reversing endian format
    std::string rev_endian(std::string data)
    {
        // Code to reverse the endian format
        // IEX uses little endian format for numerial values
        // while most of c++ is in big endian format
        std::string temp;
        for (int i = data.length() - 1; i > -1; i -= 2)
        {
            temp += data[i - 1];
            temp += data[i];
        }
        return temp;
    }

    // Data Types
    signed long read_long(std::string data)
    {
        data = rev_endian(data);
        // long is a 8 bytes signed integer
        long output = stol(data, 0, 16);
        return output;
    }

    signed long read_price(std::string data)
    {
        // Effectively same as long
        return read_long(data);
    }

    unsigned long read_int(std::string data)
    {
        // int is 4 bytes unsigned
        data = rev_endian(data);
        unsigned long output = stoul(data, 0, 16);
        return output;
    }

    unsigned long read_event_time(std::string data)
    {
        // event time is same as integer data type
        return read_int(data);
    }

    unsigned int read_short(std::string data)
    {
        // short is a 2 byte unsigned integer
        data = rev_endian(data);
        short output = stoul(data, 0, 16);
        return output;
    }

    unsigned int read_byte(std::string data)
    {
        // byte is unsigned integer
        //stoul converts string to hex to unsigned int
        data = rev_endian(data);
        int output = stoul(data, 0, 16);
        return output;
    }

    signed long read_timestamp(std::string data)
    {
        //timestamp is a 8 byte signed integer
        //same as long
        return read_long(data);
    }

    // Read strings
    //see -> https://stackoverflow.com/a/3790707
    unsigned char hexval(unsigned char c)
    {
        if ('0' <= c && c <= '9')
            return c - '0';
        else if ('a' <= c && c <= 'f')
            return c - 'a' + 10;
        else if ('A' <= c && c <= 'F')
            return c - 'A' + 10;
        else
            abort();
    }

    void hex2ascii(const std::string &in, std::string &out)
    {
        out.clear();
        out.reserve(in.length() / 2);
        for (std::string::const_iterator p = in.begin(); p != in.end(); p++)
        {
            unsigned char c = hexval(*p);
            p++;
            if (p == in.end())
                break;                 // incomplete last digit - should report error
            c = (c << 4) + hexval(*p); // + takes precedence over <<
            out.push_back(c);
        }
    }

    std::string read_string(std::string data)
    {
        //Reads string
        std::string output;
        hex2ascii(data, output);

        // Erase empty spaces
        std::string::iterator end_pos = std::remove(output.begin(), output.end(), ' ');
        output.erase(end_pos, output.end());

        return output;
    }

    // Convert flag to binary representation
    // see -> https://stackoverflow.com/a/18311086
    const char *hex_char_to_bin(char c)
    {
        // TODO handle default / error
        switch (toupper(c))
        {
        case '0':
            return "0000";
        case '1':
            return "0001";
        case '2':
            return "0010";
        case '3':
            return "0011";
        case '4':
            return "0100";
        case '5':
            return "0101";
        case '6':
            return "0110";
        case '7':
            return "0111";
        case '8':
            return "1000";
        case '9':
            return "1001";
        case 'A':
            return "1010";
        case 'B':
            return "1011";
        case 'C':
            return "1100";
        case 'D':
            return "1101";
        case 'E':
            return "1110";
        case 'F':
            return "1111";
        };

        //remove warning with default argument
        return "0000";
    }

    std::string hex_str_to_bin_str(const std::string &hex)
    {
        // TODO use a loop from <algorithm> or smth
        std::string bin;
        for (unsigned i = 0; i != hex.length(); ++i)
            bin += hex_char_to_bin(hex[i]);
        return bin;
    }

}