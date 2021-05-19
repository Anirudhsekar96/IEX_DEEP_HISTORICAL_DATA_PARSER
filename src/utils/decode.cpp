// Importing base libraries
#include <string>
#include <iostream>

// Importing our libraries
#include "message.cpp"

namespace Decode
{
    void packet_parse(std::string packet, DataStructure::string_array &outputs)
    {
        int packet_length = packet.length();

        if (packet_length > 80)
        {
            // We only care about packets which are larger than 80 (40 Bytes)
            std::string actual_message;
            std::string message_type;
            int message_len;

            // Getting the raw messages
            std::string raw_message = packet.substr(80, packet_length - 80);
            int raw_message_len = raw_message.length();

            // Every message starts with the length of the message in bytes and then the actual message itself
            int left_ptr = 0;
            while (left_ptr < raw_message_len)
            {
                message_len = DataType::read_short(raw_message.substr(left_ptr, 4));
                actual_message = raw_message.substr(left_ptr + 4, message_len * 2);

                //Getting the type of message
                message_type = actual_message.substr(0, 2);

                Message::parse_message(actual_message, message_type, outputs);

                // 4 characters for message length
                // 2 characters per hex for message
                left_ptr += message_len * 2 + 4;
            }
        }
    }
}