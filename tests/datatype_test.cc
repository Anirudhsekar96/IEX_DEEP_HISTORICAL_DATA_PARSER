#include <gtest/gtest.h>
#include <string>
#include "../src/utils/decode.cpp"

// Testing Strings
TEST(String, Symbol)
{
    const char *input = DataType::read_string("5a49455854202020").c_str();
    const char *output = "ZIEXT";
    EXPECT_STRCASEEQ(input, output);
}

TEST(String, Message_Type)
{
    const char *input = DataType::read_string("38").c_str();
    const char *output = "8";
    EXPECT_STRCASEEQ(input, output);
}

TEST(String, Message_Type2)
{
    const char *input = DataType::read_string("54").c_str();
    const char *output = "T";
    EXPECT_STRCASEEQ(input, output);
}

// Testing Integer
TEST(Int, Size1)
{
    const char *input = std::to_string(DataType::read_int("e4250000")).c_str();
    const char *output = "9700";
    EXPECT_STRCASEEQ(input, output);
}

TEST(Int, Size2)
{
    const char *input = std::to_string(DataType::read_int("64000000")).c_str();
    const char *output = "100";
    EXPECT_STRCASEEQ(input, output);
}

TEST(Int, Imbalance_shares)
{
    const char *input = std::to_string(DataType::read_int("27100000")).c_str();
    const char *output = "4135"; //"10000"; -> Bad example in IEX auction data
    EXPECT_STRCASEEQ(input, output);
}

TEST(Int, Paired_shares)
{
    const char *input = std::to_string(DataType::read_int("186a0000")).c_str();
    const char *output = "27160"; //"100000"; -> Bad example in IEX auction data
    EXPECT_STRCASEEQ(input, output);
}

// Testing Price
TEST(Price, Price1)
{
    const char *input = std::to_string(DataType::read_price("241d0f0000000000")).c_str();
    const char *output = "990500";
    EXPECT_STRCASEEQ(input, output);
}

TEST(Price, Price2)
{
    const char *input = std::to_string(DataType::read_price("181f0f0000000000")).c_str();
    const char *output = "991000";
    EXPECT_STRCASEEQ(input, output);
}

TEST(Price, Price3)
{
    const char *input = std::to_string(DataType::read_price("0c210f0000000000")).c_str();
    const char *output = "991500";
    EXPECT_STRCASEEQ(input, output);
}

TEST(Price, Price4)
{
    const char *input = std::to_string(DataType::read_price("c01c0f0000000000")).c_str();
    const char *output = "990400";
    EXPECT_STRCASEEQ(input, output);
}

TEST(Price, Price5)
{
    const char *input = std::to_string(DataType::read_price("a4990d0000000000")).c_str();
    const char *output = "891300";
    EXPECT_STRCASEEQ(input, output);
}

TEST(Price, Price6)
{
    const char *input = std::to_string(DataType::read_price("dc9f100000000000")).c_str();
    const char *output = "1089500";
    EXPECT_STRCASEEQ(input, output);
}

// Testing Long
TEST(Long, Trade_ID)
{
    const char *input = std::to_string(DataType::read_long("968f060000000000")).c_str();
    const char *output = "429974";
    EXPECT_STRCASEEQ(input, output);
}

TEST(Long, Stream_offset)
{
    const char *input = std::to_string(DataType::read_long("8ca6210000000000")).c_str();
    const char *output = "2205324";
    EXPECT_STRCASEEQ(input, output);
}
TEST(Long, First_sequence_number1)
{
    const char *input = std::to_string(DataType::read_long("cac3000000000000")).c_str();
    const char *output = "50122";
    EXPECT_STRCASEEQ(input, output);
}

TEST(Long, First_sequence_number2)
{
    const char *input = std::to_string(DataType::read_long("3430000000000000")).c_str();
    const char *output = "12340";
    EXPECT_STRCASEEQ(input, output);
}

TEST(Long, First_sequence_number3)
{
    const char *input = std::to_string(DataType::read_long("3e30000000000000")).c_str();
    const char *output = "12350";
    EXPECT_STRCASEEQ(input, output);
}
TEST(Long, First_sequence_number4)
{
    const char *input = std::to_string(DataType::read_long("d5dd000000000000")).c_str();
    const char *output = "56789";
    EXPECT_STRCASEEQ(input, output);
}
TEST(Long, First_sequence_number5)
{
    const char *input = std::to_string(DataType::read_long("dfdd000000000000")).c_str();
    const char *output = "56799";
    EXPECT_STRCASEEQ(input, output);
}