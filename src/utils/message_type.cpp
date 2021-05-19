// Importing base libraries
#include <string>
#include <iostream>

// Importing our libraries
#include "data_type.cpp"

namespace MessageType
{
    // Follows: https://iextrading.com/docs/IEX%20DEEP%20Specification.pdf

    std::string delimiter = ",";
    std::string newline = "\n";

    std::string sale_condition_flag_decipher(std::string sale_condition_flag)
    {
        // Follows Apendix A of IEX Deep Specification document
        std::string intermarket_sweep_flag = sale_condition_flag.substr(0, 1);
        std::string extended_hours_flag = sale_condition_flag.substr(1, 1);
        std::string odd_lot_flag = sale_condition_flag.substr(2, 1);
        std::string trade_through_extempt_flag = sale_condition_flag.substr(3, 1);
        std::string single_price_cross_flag = sale_condition_flag.substr(4, 1);

        // Trade Eligibility Flags
        std::string last_sale_eligible;
        std::string high_low_price_eligible;
        std::string volume_eligible = "VOLUME_ELIGIBLE";

        if ((extended_hours_flag == "0") & (odd_lot_flag == "0"))
        {
            last_sale_eligible = "LAST_SALE_ELIGIBLE";
            high_low_price_eligible = "HIGH_LOW_PRICE_ELIGIBLE";
        }
        else
        {
            last_sale_eligible = "NOT_LAST_SALE_ELIGIBLE";
            high_low_price_eligible = "NOT_HIGH_LOW_PRICE_ELIGIBLE";
        }

        // flag1
        if (intermarket_sweep_flag == "0")
        {
            intermarket_sweep_flag = "NON_INTERMARKET_SWEEP";
        }
        else if (intermarket_sweep_flag == "1")
        {
            intermarket_sweep_flag = "INTERMARKET_SWEEP";
        }

        //flag2
        if (extended_hours_flag == "0")
        {
            extended_hours_flag = "REGULAR_MARKET_TRADE_SESSION";
        }
        else if (extended_hours_flag == "1")
        {
            extended_hours_flag = "EXTENDED_HOUR_TRADE_FORM_T";
        }

        //flag3
        if (odd_lot_flag == "0")
        {
            odd_lot_flag = "ROUND_OR_MIXED_LOT_TRADE";
        }
        else if (odd_lot_flag == "1")
        {
            odd_lot_flag = "ODD_LOT_TRADE";
        }

        //flag4
        if (trade_through_extempt_flag == "0")
        {
            trade_through_extempt_flag = "TRADE_IS_SUBJECT_TO_RULE611_SEC_TRADE_THROUGH";
        }
        else if (trade_through_extempt_flag == "1")
        {
            trade_through_extempt_flag = "TRADE_IS_NOT_SUBJECT_TO_RULE611_SEC_TRADE_THROUGH";
        }

        //flag5
        if (single_price_cross_flag == "0")
        {
            single_price_cross_flag = "EXECUTION_DURING_CONTINOUS_TRADING";
        }
        else if (single_price_cross_flag == "1")
        {
            single_price_cross_flag = "SINGLE_PRICE_CROSS_TRADE";
        }

        std::string output = intermarket_sweep_flag + delimiter + extended_hours_flag + delimiter + odd_lot_flag + delimiter;
        output += trade_through_extempt_flag + delimiter + single_price_cross_flag;
        output += delimiter + last_sale_eligible + delimiter + high_low_price_eligible + delimiter + volume_eligible;

        return output;
    }

    // Individual message types
    std::string system_event_message(std::string message)
    {
        /*
            Message Type = 1 Byte = 2C
            System Event = 1 Byte = 2C
            Timestamp = 8 Bytes = 16C
        */

        std::string message_type = "SYSTEM_EVENT"; //message.substr(0,2)
        std::string system_event = message.substr(2, 2);
        std::string timestamp = std::to_string(DataType::read_timestamp(message.substr(4, 16)));

        if (system_event == "4f")
        {
            system_event = "START_OF_MESSAGES";
        }
        else if (system_event == "53")
        {
            system_event = "START_OF_SYSTEM_HOURS";
        }
        else if (system_event == "52")
        {
            system_event = "START_OF_REGULAR_MARKET_HOURS";
        }
        else if (system_event == "4d")
        {
            system_event = "END_OF_REGULAR_MARKET_HOURS";
        }
        else if (system_event == "45")
        {
            system_event = "END_OF_SYSTEM_HOURS";
        }
        else if (system_event == "43")
        {
            system_event = "END_OF_MESSAGES";
        }

        //std::string output = message_type + delimiter + system_event + delimiter + timestamp + newline;
        std::string output = timestamp + delimiter + system_event + newline;

        return output;
    }

    std::string short_sale_price_test(std::string message)
    {
        /*
            Message Type = 1 Byte = 2 C
            Short Sale Price Test Status = 1 Byte = 2C
            Timestamp = 8 Bytes = 16C
            Symbol = 8 Bytes  = 16C
            Detail = 1 Byte = 2C
        */

        std::string message_type = "SHORT_SALE_PRICE_TEST"; // message.substr(0,2)
        std::string short_sale_price_test_status = message.substr(2, 2);
        std::string timestamp = std::to_string(DataType::read_timestamp(message.substr(4, 16)));
        std::string symbol = DataType::read_string(message.substr(20, 16));
        std::string detail = message.substr(36, 2);

        if (short_sale_price_test_status == "00")
        {
            short_sale_price_test_status = "SHORT_SALE_PRICE_TEST_NOT_IN_EFFECT";
        }
        else if (short_sale_price_test_status == "01")
        {
            short_sale_price_test_status = "SHORT_SALE_PRICE_TEST_IN_EFFECT";
        }
        // short sale price restriction details
        if (detail == "20")
        {
            detail = "NO_PRICE_TEST_IN_PLACE";
        }
        else if (detail == "41")
        {
            detail = "SHORT_SALE_PRICE_RESTRICTION_ACTIVATED";
        }
        else if (detail == "43")
        {
            detail = "SHORT_SALE_PRICE_RESTRICTION_CONTINUED";
        }
        else if (detail == "44")
        {
            detail = "SHORT_SALE_PRICE_RESTRICTION_DEACTIVATED";
        }
        else if (detail == "4e")
        {
            detail = "SHORT_SALE_PRICE_RESTRICTION_NOT_AVAILABLE";
        }

        //std::string output = message_type + delimiter + short_sale_price_test_status;
        //output += delimiter + timestamp + delimiter + symbol + delimiter;
        //output += detail + newline;

        std::string output = symbol + delimiter + timestamp + delimiter;
        output += short_sale_price_test_status + delimiter + detail + newline;

        return output;
    }

    std::string operational_halt_status(std::string message)
    {
        /*
            Message Type = 1 Bytes = 2C
            Operational Halt Status = 1 Byte = 2C
            Timestamp =  8 Bytes = 16C
            Symbol = 8 Bytes = 16
        */

        std::string message_type = "OPERATIONAL_HALT"; //message.substr(0, 2);
        std::string operational_halt = message.substr(2, 2);
        std::string timestamp = std::to_string(DataType::read_timestamp(message.substr(4, 16)));
        std::string symbol = DataType::read_string(message.substr(20, 16));

        if (operational_halt == "4f")
        {
            operational_halt = "IEX_SPECIFIED_OPERATIONAL_HALT";
        }
        else if (operational_halt == "4e")
        {
            operational_halt = "IEX_NO_OPERATIONAL_HALT";
        }

        //std::string output = message_type + delimiter + operational_halt + delimiter + timestamp + delimiter + symbol + newline;
        std::string output = symbol + delimiter + timestamp + delimiter;
        output += operational_halt + newline;

        return output;
    }

    std::string trading_status(std::string message)
    {
        /*
            Message Type = 1 Byte = 2C
            Trading Status = 1 Byte = 2C
            Timestamp = 8 Bytes = 16C
            Symbol = 8 Bytes = 16C
            Reason = 8 Bytes = 16C
        */

        std::string message_type = "TRADING_STATUS"; //message.substr(0,2);
        std::string trading_sta = message.substr(2, 2);
        std::string timestamp = std::to_string(DataType::read_timestamp(message.substr(4, 16)));
        std::string symbol = DataType::read_string(message.substr(20, 16));
        std::string reason = DataType::read_string(message.substr(36, 16));

        // Cleaning Reason when it is empty
        if (reason == "")
        {
            reason = "REASON_NOT_APPLICABLE";
        }

        // deciphering trading status - change to switch case
        // Also deciphering reason_decode
        if (trading_sta == "48")
        {
            trading_sta = "TRADING_HALTED_ACCROSS_ALL_US_EQUITY_MARKETS";
            if (reason == "T1")
            {
                reason = "HALT_NEWS_PENDING";
            }
            else if (reason == "IPO1")
            {
                reason = "IPO_NOT_YET_TRADING";
            }
            else if (reason == "IPOD")
            {
                reason = "IPO_DEFFERED";
            }
            else if (reason == "MCB3")
            {
                reason = "MARKET_WIDE_CIRCUIT_BREAKER_3_BREACHED";
            }
            else if (reason == "NA")
            {
                reason = "REASON_NOT_AVAILABLE";
            }
        }
        else if ((trading_sta == "4f") or (trading_sta == "50"))
        {
            if (trading_sta == "4f")
            {
                trading_sta = "TRADING_HALT_RELEASED_INTO_ORDER_ACCEPTANCE_ON_IEX";
            }
            else if (trading_sta == "50")
            {
                trading_sta = "TRADING_PAUSED_AND_ORDER_ACCEPTANCE_ON_IEX";
            }

            if (reason == "T2")
            {
                reason = "HALT_NEW_DISSEMINATION";
            }
            else if (reason == "IPO2")
            {
                reason = "IPO_ORDER_ACCEPTANCE_PERIOD";
            }
            else if (reason == "IPO3")
            {
                reason = "IPO_PRE_LAUNCH_PERIOD";
            }
            else if (reason == "MCB1")
            {
                reason = "MARKET_WIDE_CIRCUIT_BREAKER_1_BREACHED";
            }
            else if (reason == "MCB2")
            {
                reason = "MARKET_WIDE_CIRUIT_BREAKER_2_BREACHED";
            }
        }
        else if (trading_sta == "54")
        {
            trading_sta = "TRADING_ON_IEX";
        }

        //std::string output = message_type + delimiter + trading_sta + delimiter + timestamp + delimiter + symbol + delimiter + reason + newline;

        std::string output = symbol + delimiter + timestamp + delimiter;
        output += trading_sta + delimiter + reason + newline;

        return output;
    }

    std::string trade_report(std::string message)
    {
        /*
            Message Type = 1 Byte = 2C
            Sale Condition Flag = 1 Byte = 2C
            Timestamp = 8 Bytes = 16C
            Symbol = 8 Bytes = 16C
            Size = 4 Byte = 8C
            Price = 8 Bytes = 16C
            Trade ID = 8 Bytes = 16C
        */

        std::string message_type = "TRADE_REPORT"; // message.substr(0,2);
        std::string sale_condition_flag = MessageType::sale_condition_flag_decipher(DataType::hex_str_to_bin_str(message.substr(2, 2)));
        std::string timestamp = std::to_string(DataType::read_timestamp(message.substr(4, 16)));
        std::string symbol = DataType::read_string(message.substr(20, 16));
        std::string size = std::to_string(DataType::read_int(message.substr(36, 8)));
        std::string price = std::to_string(DataType::read_price(message.substr(44, 16)));
        std::string trade_id = std::to_string(DataType::read_long(message.substr(60, 16)));

        //std::string output = message_type + delimiter + sale_condition_flag + delimiter + timestamp + delimiter;
        //output += symbol + delimiter + size + delimiter + price + delimiter + trade_id + newline;

        std::string output = symbol + delimiter + timestamp + delimiter;
        output += price + delimiter + size + delimiter;
        output += trade_id + delimiter + sale_condition_flag + newline;

        return output;
    }

    std::string official_price(std::string message)
    {
        /*
            Message Type = 1 Byte =2C
            Price Type = 1 Byte = 2C
            Timestamp = 8 Bytes = 16C
            Symbol = 8 Bytes = 16C
            Official Price = 8 Bytes = 16C
        */
        std::string message_type = "OFFICIAL_PRICE"; //message.substr(0,2);
        std::string price_type = message.substr(2, 2);
        std::string timestamp = std::to_string(DataType::read_timestamp(message.substr(4, 16)));
        std::string symbol = DataType::read_string(message.substr(20, 16));
        std::string official_price = std::to_string(DataType::read_price((message.substr(36, 16))));

        // Deciphering price type
        if (price_type == "51")
        {
            price_type = "IEX_OFFICIAL_OPENING_PRICE";
        }
        else if (price_type == "4d")
        {
            price_type = "IEX_OFFICIAL_CLOSING_PRICE";
        }
        //std::string output = message_type + delimiter + price_type + delimiter;
        //output += timestamp + delimiter + symbol + official_price + newline;

        std::string output = symbol + delimiter + timestamp + delimiter + official_price;
        output += delimiter + price_type + newline;

        return output;
    }

    std::string price_level_update(std::string message)
    {
        /*
            Message Type = 1 Byte = 2C
            Event_flag = 1 Byte = 2C // also calling it event type
            Timestamp = 8 Bytes = 16C
            Symbol = 8 Bytes = 16C
            Size = 4 Bytes = 8C
            Price = 8 Bytes = 16C
        */

        std::string message_type = "PRICE_LEVEL_UPDATE"; //message.substr(0, 2);
        std::string event_type = message.substr(2, 2);
        std::string timestamp = std::to_string(DataType::read_timestamp(message.substr(4, 16)));
        std::string symbol = DataType::read_string(message.substr(20, 16));
        std::string size = std::to_string(DataType::read_int(message.substr(36, 8)));
        std::string price = std::to_string(DataType::read_price(message.substr(44, 16)));

        // Deciphering the message type
        if (message_type == "38")
        {
            message_type = "PRICE_LEVEL_UPDATE_ON_BUY_SIDE";
        }
        else if (message_type == "35")
        {
            message_type = "PRICE_LEVEL_UPDATE_ON_SELL_SIDE";
        }

        //Deciphering the event type
        if (event_type == "00")
        {
            event_type = "ORDER_BOOK_IN_TRANSITION";
        }
        else if (event_type == "01")
        {
            event_type = "ORDER_BOOK_EVENT_PROCESSING_COMPLETED";
        }

        //std::string output = message_type + delimiter + event_type + delimiter;
        //output += timestamp + delimiter + symbol + delimiter + size + delimiter + price + newline;

        std::string output = symbol + delimiter + timestamp + delimiter + price + delimiter;
        output += size + delimiter + event_type + newline;
        return output;
    }

    std::string auction_message(std::string message)
    {
        /*
            Message Type = 1 Byte = 2C
            Auction Type = 1 Byte = 2C
            Timestamp = 8 Bytes = 16C
            Symbol = 8 Bytes = 16C
            Paired_shared = 4 Bytes = 8C
            Reference Price = 8 Bytes = 16C
            Indicative Clearing Price = 8 Bytes = 16C
            Imbalance Share = 4 Bytes = 8C
            Imbalance Side = 1 Byte = 2C
            Extension Number = 1 Byte = 2C
            Auction Time Scheduled = 4 Bytes = 8C
            Auction Book Clearing Price = 8 Bytes = 16C
            Collar Reference Price = 8 Bytes = 16C
            Lower Auction Collar = 8 Bytes = 16C
            Upper Auction Collar = 8 Bytes = 16C
        */
        std::string message_type = "AUCTION_MESSAGE"; //message.substr(0,2);
        std::string auction_type = message.substr(2, 2);
        std::string timestamp = std::to_string(DataType::read_timestamp(message.substr(4, 16)));
        std::string symbol = DataType::read_string(message.substr(20, 16));
        std::string paired_shares = std::to_string(DataType::read_int(message.substr(36, 8)));
        std::string reference_price = std::to_string(DataType::read_price(message.substr(44, 16)));
        std::string indicative_clearing_price = std::to_string(DataType::read_price(message.substr(60, 16)));
        std::string imbalance_share = std::to_string(DataType::read_int(message.substr(76, 8)));
        std::string imbalance_side = message.substr(84, 2);
        std::string extension_number = std::to_string(DataType::read_byte(message.substr(86, 2)));
        std::string auction_time = std::to_string(DataType::read_event_time(message.substr(88, 8)));
        std::string auction_book_clearing = std::to_string(DataType::read_price(message.substr(96, 16)));
        std::string collar_reference_price = std::to_string(DataType::read_price(message.substr(112, 16)));
        std::string lower_auction_collar = std::to_string(DataType::read_price(message.substr(128, 16)));
        std::string upper_auction_collar = std::to_string(DataType::read_price(message.substr(144, 16)));

        // Deciphering Auction Type
        if (auction_type == "4f")
        {
            auction_type = "OPENING_AUCTION";
        }
        else if (auction_type == "43")
        {
            auction_type = "CLOSING_AUCTION";
        }
        else if (auction_type == "49")
        {
            auction_type = "IPO_AUCTION";
        }
        else if (auction_type == "48")
        {
            auction_type = "HALT_AUCTION";
        }
        else if (auction_type == "56")
        {
            auction_type = "VOLATILITY_AUCTION";
        }

        //Deciphering Imbalence side
        if (imbalance_side == "42")
        {
            imbalance_side = "BUY_SIDE_IMBALANCE";
        }
        else if (imbalance_side == "53")
        {
            imbalance_side = "SELL_SIDE_IMBALANCE";
        }
        else if (imbalance_side == "4e")
        {
            imbalance_side = "NO_IMBALANCE";
        }

        //std::string output = message_type + delimiter + auction_type + delimiter + timestamp + delimiter;
        //output += symbol + delimiter + paired_shares + delimiter + reference_price + delimiter;
        //output += indicative_clearing_price + delimiter + imbalance_share + delimiter;
        //output += imbalance_side + delimiter + extension_number + delimiter + auction_time;
        //output += delimiter + auction_book_clearing + delimiter + collar_reference_price;
        //output += delimiter + lower_auction_collar + delimiter + upper_auction_collar + newline;

        std::string output = symbol + delimiter + timestamp + delimiter;
        output += auction_type + delimiter + paired_shares + delimiter;
        output += reference_price + delimiter + indicative_clearing_price + delimiter + imbalance_share + delimiter;
        output += imbalance_side + delimiter + extension_number + delimiter + auction_time;
        output += delimiter + auction_book_clearing + delimiter + collar_reference_price;
        output += delimiter + lower_auction_collar + delimiter + upper_auction_collar + newline;

        return output;
    }

    std::string security_event(std::string message)
    {
        /*
            Message Type = 1 Byte = 2C
            Security Event = 1 Byte = 2C
            Timestamp = 8 Bytes = 16C
            Symbol = 8 Bytes = 16C
        */

        std::string message_type = "SECURITY_EVENT"; // message.substr(0,2);
        std::string security_event_flag = message.substr(2, 2);
        std::string timestamp = std::to_string(DataType::read_timestamp(message.substr(4, 16)));
        std::string symbol = DataType::read_string(message.substr(20, 16));

        // Reading security event flag
        if (security_event_flag == "4f")
        {
            security_event_flag = "OPENING_PROCESS_COMPLETED";
        }
        else if (security_event_flag == "43")
        {
            security_event_flag = "CLOSING_PROCESS_COMPLETED";
        }

        //std::string output = message_type + delimiter + security_event_flag + delimiter;
        //output += timestamp + delimiter + symbol + newline;

        std::string output = symbol + delimiter + timestamp + delimiter;
        output += security_event_flag + newline;

        return output;
    }

    std::string security_directory(std::string message)
    {
        /*
            Message Type = 1 Byte = 2C
            Flags = 1 Byte = 2C
            Timestamp = 8 Bytes = 16C
            Symbol = 8 Bytes = 16C
            Round Lot Size = 4 Bytes = 8C
            Adjusted POC Price = 8 Bytes = 16C
            LULD Tier = 1 Byte = 2C
        */

        std::string message_type = "SECURITY_DIRECTORY"; //message.substr(0,2);
        std::string flags = DataType::hex_str_to_bin_str(message.substr(2, 2));
        std::string timestamp = std::to_string(DataType::read_timestamp(message.substr(4, 16)));
        std::string symbol = DataType::read_string(message.substr(20, 16));
        std::string round_lot_size = std::to_string(DataType::read_int(message.substr(36, 8)));
        std::string adjusted_poc_price = std::to_string(DataType::read_price(message.substr(44, 16)));
        std::string luld_tier = message.substr(60, 2);

        // Deciphering LULD Tier
        if (luld_tier == "00")
        {
            luld_tier = "NOT_APPLICABLE";
        }
        else if (luld_tier == "01")
        {
            luld_tier = "TIER_1_NMS_STOCK";
        }
        else if (luld_tier == "02")
        {
            luld_tier = "TIER_2_NMS_STOCK";
        }

        // Deciphering flags
        std::string test_security_flag = flags.substr(0, 1);
        std::string when_issued_security_flag = flags.substr(1, 1);
        std::string exchange_traded_product_flag = flags.substr(2, 1);

        if (test_security_flag == "0")
        {
            test_security_flag = "NOT_TEST_SECURITY";
        }
        else if (test_security_flag == "1")
        {
            test_security_flag = "TEST_SECURITY";
        }

        if (when_issued_security_flag == "0")
        {
            when_issued_security_flag = "NOT_WHEN_ISSUED_SECURITY";
        }
        else if (when_issued_security_flag == "1")
        {
            when_issued_security_flag = "WHEN_ISSUED_SECURITY";
        }

        if (exchange_traded_product_flag == "0")
        {
            exchange_traded_product_flag = "NOT_EXCHANGE_TRADED_PRODUCT";
        }
        else if (exchange_traded_product_flag == "1")
        {
            exchange_traded_product_flag = "EXCHANGE_TRADED_PRODUCT";
        }

        //std::string output = message_type + delimiter + test_security_flag + delimiter + when_issued_security_flag + delimiter;
        //output += exchange_traded_product_flag + delimiter + timestamp + delimiter;
        //output += symbol + delimiter + round_lot_size + delimiter;
        //output += adjusted_poc_price + delimiter + luld_tier + newline;

        std::string output = symbol + delimiter + timestamp + delimiter;
        output += luld_tier + delimiter + adjusted_poc_price + delimiter;
        output += round_lot_size + delimiter + test_security_flag + delimiter;
        output += when_issued_security_flag + delimiter;
        output += exchange_traded_product_flag + newline;

        return output;
    }

    std::string trade_break_message(std::string message)
    {
        // Appendix A for flag values
        /*
            Message Type = 1 Byte = 2C
            Sale Condition Flag = 1 Byte = 2C
            Timestamp = 8 Bytes = 16C
            Symbol = 8 Bytes = 16C
            Size = 4 Bytes = 8C
            Price = 8 Bytes = 16C
            Trade ID = 8 Bytes = 16C
        */
        std::string message_type = "TRADE_BREAK"; //message.substr(0,2);
        std::string sale_condition_flag = sale_condition_flag_decipher(DataType::hex_str_to_bin_str(message.substr(2, 2)));
        std::string timestamp = std::to_string(DataType::read_timestamp(message.substr(4, 16)));
        std::string symbol = DataType::read_string(message.substr(20, 16));
        std::string size = std::to_string(DataType::read_int(message.substr(36, 8)));
        std::string price = std::to_string(DataType::read_price(message.substr(44, 16)));
        std::string trade_id = std::to_string(DataType::read_long(message.substr(60, 16)));

        //std::string output = message_type + delimiter + sale_condition_flag + delimiter;
        //output += timestamp + delimiter + symbol + delimiter;
        //output += size + delimiter + price + delimiter + trade_id + newline;

        std::string output = symbol + delimiter + timestamp + delimiter;
        output += price + delimiter + size + delimiter;
        output += sale_condition_flag + delimiter + trade_id + newline;
        return output;
    }
}