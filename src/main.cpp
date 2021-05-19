// Importing libraries
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

// Reading our own functions
#include "utils/decode.cpp"

int main(int argc, char *argv[])
{
    // Initializing IO path variables
    std::string read_file_path;
    std::string write_file_path;

    // Initializing the string containing raw packets
    std::string packet;

    // Initializing output data structure
    DataStructure::string_array outputs;
    DataStructure::string_array_init(outputs);

    if (argc == 3)
    {
        // Command Line Arguments, needs read and write path
        read_file_path = argv[1];
        write_file_path = argv[2];
    }
    else
    {
        //Unkown commands, exit with error status
        return -1;
    }

    std::ifstream raw_file(read_file_path);

    if (raw_file.is_open())
    {
        // Read entire file into memory
        std::stringstream buffer;
        buffer << raw_file.rdbuf();

        // Processing packet by packet
        while (std::getline(buffer, packet, '\n'))
        {
            // Cleaning unwanted '\n' from the packets
            packet.erase(remove(packet.begin(), packet.end(), '\n'), packet.end());

            // Decoding the packets
            Decode::packet_parse(packet, outputs);
        }

        raw_file.close();

        // Writing files to disk
        io::save_file(write_file_path, outputs);
    }
    else
    {
        // Unable to open the files
        return -1;
    }

    return 0;
}