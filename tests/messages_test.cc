#include <gtest/gtest.h>
#include <string>
#include "../src/utils/decode.cpp"

TEST(VALID_MESSAGE, VALID_MESSAGE)
{
    DataStructure::string_array outputs;
    DataStructure::string_array_init(outputs);

    std::string message1 = "534500a09997e93db614";
    std::string message2 = "44800020897b5a1fb6145a4945585420202064000000241d0f000000000001";
    std::string message3 = "4848ac63c02096866d145a4945585420202054312020";
    std::string message4 = "4f4fac63c02096866d145a49455854202020";
    std::string message5 = "5001ac63c02096866d145a4945585420202041";
    std::string message6 = "454f00f0302a5b25b6145a49455854202020";
    std::string message7 = "3801ac63c02096866d145a49455854202020e4250000241d0f0000000000";
    std::string message8 = "5400c3dff705a2866d145a4945585420202064000000241d0f0000000000968f060000000000";
    std::string message9 = "585100f0302a5b25b6145a49455854202020241d0f0000000000";
    std::string message10 = "4200b28fa5a0ab866d145a4945585420202064000000241d0f0000000000968f060000000000";
    std::string message11 = "4143ddc7f09a1a3ab6145a49455854202020186a0000241d0f0000000000181f0f000000000027100000420080e6f4580c210f0000000000c01c0f0000000000a4990d0000000000dc9f100000000000";
    std::string message12 = "3501ac63c02096866d145a49455854202020e4250000241d0f0000000000";

    Message::parse_message(message1, message1.substr(0, 2), outputs);
    Message::parse_message(message2, message2.substr(0, 2), outputs);
    Message::parse_message(message3, message3.substr(0, 2), outputs);
    Message::parse_message(message4, message4.substr(0, 2), outputs);
    Message::parse_message(message5, message5.substr(0, 2), outputs);
    Message::parse_message(message6, message6.substr(0, 2), outputs);
    Message::parse_message(message7, message7.substr(0, 2), outputs);
    Message::parse_message(message8, message8.substr(0, 2), outputs);
    Message::parse_message(message9, message9.substr(0, 2), outputs);
    Message::parse_message(message10, message10.substr(0, 2), outputs);
    Message::parse_message(message11, message11.substr(0, 2), outputs);
    Message::parse_message(message12, message12.substr(0, 2), outputs);

    const char *output1 = "TIMESTAMP,EVENT_TYPE\n1492448400000000000,END_OF_SYSTEM_HOURS\n";
    const char *output2 = "SYMBOL,TIMESTAMP,LULD_TIER,ADJUSTED_POC_PRICE,ROUND_LOT_SIZE,TEST_SECURITY,WHEN_ISSUED_SECURITY,EXCHANGE_TRADED_PRODUCT\nZIEXT,1492414800000000000,TIER_1_NMS_STOCK,990500,100,TEST_SECURITY,NOT_WHEN_ISSUED_SECURITY,NOT_EXCHANGE_TRADED_PRODUCT\n";
    const char *output3 = "SYMBOL,TIMESTAMP,STATUS,REASON\nZIEXT,1471980632572715948,TRADING_HALTED_ACCROSS_ALL_US_EQUITY_MARKETS,HALT_NEWS_PENDING\n";
    const char *output4 = "SYMBOL,TIMESTAMP,STATUS\nZIEXT,1471980632572715948,IEX_SPECIFIED_OPERATIONAL_HALT\n";
    const char *output5 = "SYMBOL,TIMESTAMP,STATUS,DETAILS\nZIEXT,1471980632572715948,SHORT_SALE_PRICE_TEST_IN_EFFECT,SHORT_SALE_PRICE_RESTRICTION_ACTIVATED\n";
    const char *output6 = "SYMBOL,TIMESTAMP,EVENT_TYPE\nZIEXT,1492421400000000000,OPENING_PROCESS_COMPLETED\n";
    const char *output7 = "SYMBOL,TIMESTAMP,PRICE,SIZE,EVENT_TYPE\nZIEXT,1471980632572715948,990500,9700,ORDER_BOOK_EVENT_PROCESSING_COMPLETED\n";
    const char *output8 = "SYMBOL,TIMESTAMP,PRICE,SIZE,TRADE_ID,INTERMARKET_SWEEP_FLAG,EXTENDED_HOURS_FLAG,ODD_LOT_FLAG,TRADE_THROUGH_EXEMPT_FLAG,SINGLE_PRICE_CROSS_FLAG,LAST_SALE_ELIGIBLE_FLAG,HIGH_LOW_PRICE_ELIGIBLE_FLAG,VOLUME_ELIGIBLE_FLAG\nZIEXT,1471980683662974915,990500,100,429974,NON_INTERMARKET_SWEEP,REGULAR_MARKET_TRADE_SESSION,ROUND_OR_MIXED_LOT_TRADE,TRADE_IS_SUBJECT_TO_RULE611_SEC_TRADE_THROUGH,EXECUTION_DURING_CONTINOUS_TRADING,LAST_SALE_ELIGIBLE,HIGH_LOW_PRICE_ELIGIBLE,VOLUME_ELIGIBLE\n";
    const char *output9 = "SYMBOL,TIMESTAMP,PRICE,PRICE_TYPE\nZIEXT,1492421400000000000,990500,IEX_OFFICIAL_OPENING_PRICE\n";
    const char *output10 = "SYMBOL,TIMESTAMP,PRICE,SIZE,INTERMARKET_SWEEP_FLAG,EXTENDED_HOURS_FLAG,ODD_LOT_FLAG,TRADE_THROUGH_EXEMPT_FLAG,SINGLE_PRICE_CROSS_FLAG,LAST_SALE_ELIGIBLE_FLAG,HIGH_LOW_PRICE_ELIGIBLE_FLAG,VOLUME_ELIGIBLE_FLAG,TRADE_ID\nZIEXT,1471980724912754610,990500,100,NON_INTERMARKET_SWEEP,REGULAR_MARKET_TRADE_SESSION,ROUND_OR_MIXED_LOT_TRADE,TRADE_IS_SUBJECT_TO_RULE611_SEC_TRADE_THROUGH,EXECUTION_DURING_CONTINOUS_TRADING,LAST_SALE_ELIGIBLE,HIGH_LOW_PRICE_ELIGIBLE,VOLUME_ELIGIBLE,429974\n";
    const char *output11 = "SYMBOL,TIMESTAMP,EVENT_TYPE,PAIRED_SHARES,REFERENCE_PRICE,INDICATIVE_CLEARING_PRICE,IMBALANCE_SHARES,IMBALANCE_SIDE,EXTENSION_NUMBER,SCHEDULED_AUCTION_TIME,AUCTION_BOOK_CLEARING_PRICE,COLLAR_REFERENCE_PRICE,LOWER_AUCTION_COLLAR,UPPER_AUCTION_COLLAR\nZIEXT,1492444212462929885,CLOSING_AUCTION,27160,990500,991000,4135,BUY_SIDE_IMBALANCE,0,1492444800,991500,990400,891300,1089500\n";
    const char *output12 = "SYMBOL,TIMESTAMP,PRICE,SIZE,EVENT_TYPE\nZIEXT,1471980632572715948,990500,9700,ORDER_BOOK_EVENT_PROCESSING_COMPLETED\n";

    const char *input1 = outputs.SYSTEM_EVENT.c_str();
    const char *input2 = outputs.SECURITY_DIRECTORY.c_str();
    const char *input3 = outputs.TRADING_STATUS.c_str();
    const char *input4 = outputs.OPERATIONAL_HALT_STATUS.c_str();
    const char *input5 = outputs.SHORT_SALE_PRICE_TEST.c_str();
    const char *input6 = outputs.SECURITY_EVENT.c_str();
    const char *input7 = outputs.PRICE_LEVEL_UPDATE_BUY_SIDE.c_str();
    const char *input8 = outputs.TRADE_REPORT.c_str();
    const char *input9 = outputs.OFFICIAL_PRICE.c_str();
    const char *input10 = outputs.TRADE_BREAK.c_str();
    const char *input11 = outputs.AUCTION.c_str();
    const char *input12 = outputs.PRICE_LEVEL_UPDATE_SELL_SIDE.c_str();

    EXPECT_STRCASEEQ(input1, output1);   //system event
    EXPECT_STRCASEEQ(input2, output2);   //security directory
    EXPECT_STRCASEEQ(input3, output3);   //trading status
    EXPECT_STRCASEEQ(input4, output4);   //operational halt status
    EXPECT_STRCASEEQ(input5, output5);   //short sale price test
    EXPECT_STRCASEEQ(input6, output6);   //security event
    EXPECT_STRCASEEQ(input7, output7);   //price level update buy side
    EXPECT_STRCASEEQ(input8, output8);   //trade report
    EXPECT_STRCASEEQ(input9, output9);   //official price
    EXPECT_STRCASEEQ(input10, output10); //trade break
    EXPECT_STRCASEEQ(input11, output11); //auction
    EXPECT_STRCASEEQ(input12, output12); //price level update sell side
}

TEST(INVALID_MESSAGE, NON_STANDARD_SIZE)
{
    DataStructure::string_array outputs;
    DataStructure::string_array_init(outputs);

    std::string message = "534500a09997e93db61";
    Message::parse_message(message, message.substr(0, 2), outputs);

    const char *input = outputs.UNKOWN_MESSAGE.c_str();
    const char *output = "RAW_MESSAGE\n534500a09997e93db61";

    EXPECT_STRCASEEQ(input, output);
}

TEST(INVALID_MESSAGE, INVALID_MESSAGE_TYPE)
{
    DataStructure::string_array outputs;
    DataStructure::string_array_init(outputs);

    std::string message = "104500a09997e93db614";
    Message::parse_message(message, message.substr(0, 2), outputs);

    const char *input = outputs.UNKOWN_MESSAGE.c_str();
    const char *output = "RAW_MESSAGE\n104500a09997e93db614";

    EXPECT_STRCASEEQ(input, output);
}