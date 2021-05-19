// Importing base libaries
#include <string>
#include <iostream>

// Importing our libaries
#include "message_type.cpp"
#include "io.cpp"

namespace Message
{
    void parse_message(std::string message, std::string message_type, DataStructure::string_array &outputs)
    {
        //ToDo: Convert to switch case
        int len = message.length();

        if ((message_type == "38") & (len == 60))
        {
            // price level update on buy side
            outputs.PRICE_LEVEL_UPDATE_BUY_SIDE += MessageType::price_level_update(message);
        }

        else if ((message_type == "35") & (len == 60))
        {
            // price level update on sell side
            outputs.PRICE_LEVEL_UPDATE_SELL_SIDE += MessageType::price_level_update(message);
        }

        else if ((message_type == "54") & (len == 76))
        {
            // trade report
            outputs.TRADE_REPORT += MessageType::trade_report(message);
        }

        else if ((message_type == "58") & (len == 52))
        {
            // official price
            outputs.OFFICIAL_PRICE += MessageType::official_price(message);
        }

        else if ((message_type == "50") & (len == 38))
        {
            // short sale price test
            outputs.SHORT_SALE_PRICE_TEST += MessageType::short_sale_price_test(message);
        }

        else if ((message_type == "48") & (len == 44))
        {
            // trading status
            outputs.TRADING_STATUS += MessageType::trading_status(message);
        }

        else if ((message_type == "4f") & (len == 36))
        {
            // operational halt status
            outputs.OPERATIONAL_HALT_STATUS += MessageType::operational_halt_status(message);
        }

        else if ((message_type == "53") & (len == 20))
        {
            // system event message
            outputs.SYSTEM_EVENT += MessageType::system_event_message(message);
        }

        else if ((message_type == "44") & (len == 62))
        {
            // security directory message
            outputs.SECURITY_DIRECTORY += MessageType::security_directory(message);
        }

        else if ((message_type == "45") & (len == 36))
        {
            // security event message
            outputs.SECURITY_EVENT += MessageType::security_event(message);
        }

        else if ((message_type == "42") & (len == 76))
        {
            // trade break message
            outputs.TRADE_BREAK += MessageType::trade_break_message(message);
        }

        else if ((message_type == "41") & (len == 160))
        {
            // auction message
            outputs.AUCTION += MessageType::auction_message(message);
        }
        else
        {
            outputs.UNKOWN_MESSAGE += message;
        }
    }
}