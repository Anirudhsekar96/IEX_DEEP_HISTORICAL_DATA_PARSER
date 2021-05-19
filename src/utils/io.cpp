#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "data_structure.cpp"

namespace io
{

    void save_file(std::string write_file_path, DataStructure::string_array outputs)
    {
        /*
            Saves the data structure into individual csv files
        */

        // Creates a directory for the files
        std::filesystem::create_directories(write_file_path);

        // Creating individual csvs for each type of message
        std::ofstream processed_file[13];

        // PRICE_LEVEL_UPDATE_BUY_SIDE
        processed_file[0].open(write_file_path + "/PRICE_LEVEL_UPDATE_BUY_SIDE.csv", std::ios_base::app);
        processed_file[0] << outputs.PRICE_LEVEL_UPDATE_BUY_SIDE;

        // PRICE_LEVEL_UPDATE_SELL_SIDE
        processed_file[1].open(write_file_path + "/PRICE_LEVEL_UPDATE_SELL_SIDE.csv", std::ios_base::app);
        processed_file[1] << outputs.PRICE_LEVEL_UPDATE_SELL_SIDE;

        // TRADE_REPORT
        processed_file[2].open(write_file_path + "/TRADE_REPORT.csv", std::ios_base::app);
        processed_file[2] << outputs.TRADE_REPORT;

        // OFFICIAL_PRICE
        processed_file[3].open(write_file_path + "/OFFICIAL_PRICE.csv", std::ios_base::app);
        processed_file[3] << outputs.OFFICIAL_PRICE;

        // SHORT_SALE_PRICE_TEST
        processed_file[4].open(write_file_path + "/SHORT_SALE_PRICE_TEST.csv", std::ios_base::app);
        processed_file[4] << outputs.SHORT_SALE_PRICE_TEST;

        // TRADING_STATUS
        processed_file[5].open(write_file_path + "/TRADING_STATUS.csv", std::ios_base::app);
        processed_file[5] << outputs.TRADING_STATUS;

        // OPERATIONAL_HALT_STATUS
        processed_file[6].open(write_file_path + "/OPERATIONAL_HALT_STATUS.csv", std::ios_base::app);
        processed_file[6] << outputs.OPERATIONAL_HALT_STATUS;

        // SYSTEM_EVENT
        processed_file[7].open(write_file_path + "/SYSTEM_EVENT.csv", std::ios_base::app);
        processed_file[7] << outputs.SYSTEM_EVENT;

        // SECURITY_DIRECTORY
        processed_file[8].open(write_file_path + "/SECURITY_DIRECTORY.csv", std::ios_base::app);
        processed_file[8] << outputs.SECURITY_DIRECTORY;

        // SECURITY_EVENT
        processed_file[9].open(write_file_path + "/SECURITY_EVENT.csv", std::ios_base::app);
        processed_file[9] << outputs.SECURITY_EVENT;

        // TRADE_BREAK
        processed_file[10].open(write_file_path + "/TRADE_BREAK.csv", std::ios_base::app);
        processed_file[10] << outputs.TRADE_BREAK;

        // AUCTION
        processed_file[11].open(write_file_path + "/AUCTION.csv", std::ios_base::app);
        processed_file[11] << outputs.AUCTION;

        // UNKOWN_MESSAGE
        processed_file[12].open(write_file_path + "/UNKOWN_MESSAGE.csv", std::ios_base::app);
        processed_file[12] << outputs.UNKOWN_MESSAGE;

        //std::cout << "Outputs are saved";
    }
}