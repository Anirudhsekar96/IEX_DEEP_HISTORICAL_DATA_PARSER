#include <string>

namespace DataStructure
{
    struct string_array
    {
        std::string PRICE_LEVEL_UPDATE_BUY_SIDE;
        std::string PRICE_LEVEL_UPDATE_SELL_SIDE;
        std::string TRADE_REPORT;
        std::string OFFICIAL_PRICE;
        std::string SHORT_SALE_PRICE_TEST;
        std::string TRADING_STATUS;
        std::string OPERATIONAL_HALT_STATUS;
        std::string SYSTEM_EVENT;
        std::string SECURITY_DIRECTORY;
        std::string SECURITY_EVENT;
        std::string TRADE_BREAK;
        std::string AUCTION;
        std::string UNKOWN_MESSAGE;
    };

    void string_array_init(string_array &results)
    {
        /*
            Initializes a string array data structure with headers for csv
        */

        // CSV headers for each file
        results.PRICE_LEVEL_UPDATE_BUY_SIDE = "SYMBOL,TIMESTAMP,PRICE,SIZE,EVENT_TYPE\n";
        results.PRICE_LEVEL_UPDATE_SELL_SIDE = "SYMBOL,TIMESTAMP,PRICE,SIZE,EVENT_TYPE\n";
        results.TRADE_REPORT = "SYMBOL,TIMESTAMP,PRICE,SIZE,TRADE_ID,INTERMARKET_SWEEP_FLAG,EXTENDED_HOURS_FLAG,ODD_LOT_FLAG,TRADE_THROUGH_EXEMPT_FLAG,SINGLE_PRICE_CROSS_FLAG,LAST_SALE_ELIGIBLE_FLAG,HIGH_LOW_PRICE_ELIGIBLE_FLAG,VOLUME_ELIGIBLE_FLAG\n"; //SALE_CONDITION has multiple columns
        results.OFFICIAL_PRICE = "SYMBOL,TIMESTAMP,PRICE,PRICE_TYPE\n";
        results.SHORT_SALE_PRICE_TEST = "SYMBOL,TIMESTAMP,STATUS,DETAILS\n";
        results.TRADING_STATUS = "SYMBOL,TIMESTAMP,STATUS,REASON\n";
        results.OPERATIONAL_HALT_STATUS = "SYMBOL,TIMESTAMP,STATUS\n";
        results.SYSTEM_EVENT = "TIMESTAMP,EVENT_TYPE\n";
        results.SECURITY_DIRECTORY = "SYMBOL,TIMESTAMP,LULD_TIER,ADJUSTED_POC_PRICE,ROUND_LOT_SIZE,TEST_SECURITY,WHEN_ISSUED_SECURITY,EXCHANGE_TRADED_PRODUCT\n";
        results.SECURITY_EVENT = "SYMBOL,TIMESTAMP,EVENT_TYPE\n";
        results.TRADE_BREAK = "SYMBOL,TIMESTAMP,PRICE,SIZE,INTERMARKET_SWEEP_FLAG,EXTENDED_HOURS_FLAG,ODD_LOT_FLAG,TRADE_THROUGH_EXEMPT_FLAG,SINGLE_PRICE_CROSS_FLAG,LAST_SALE_ELIGIBLE_FLAG,HIGH_LOW_PRICE_ELIGIBLE_FLAG,VOLUME_ELIGIBLE_FLAG,TRADE_ID\n"; // SALE_CONDITION has multiple columns
        results.AUCTION = "SYMBOL,TIMESTAMP,EVENT_TYPE,PAIRED_SHARES,REFERENCE_PRICE,INDICATIVE_CLEARING_PRICE,IMBALANCE_SHARES,IMBALANCE_SIDE,EXTENSION_NUMBER,SCHEDULED_AUCTION_TIME,AUCTION_BOOK_CLEARING_PRICE,COLLAR_REFERENCE_PRICE,LOWER_AUCTION_COLLAR,UPPER_AUCTION_COLLAR\n";
        results.UNKOWN_MESSAGE = "RAW_MESSAGE\n";
    }
}