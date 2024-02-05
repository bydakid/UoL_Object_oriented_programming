#pragma once
#include <string>

enum class OrderBookType{bid, ask, unknown}; // enum class represent the type of OrderBookEntry

class OrderBookEntry
{
    public:
        // constructor that takes five parameters and creates an OrderBookEntry object
        OrderBookEntry( double _price,
                        double _amount,
                        std::string _currenTime,
                        std::string _product,
                        OrderBookType _orderType);
        static OrderBookType stringToOrderBookType(std::string s); // static method takes string as input and returns an OrderBookType value

        double price; // price of OrderBookEntry
        double amount; // amount of OrderBookEntry
        std::string currenTime; // currentime of OrderBookEntry
        std::string product; // product of OrderBookEntry
        OrderBookType orderType; // ordertype of OrderBookEntry
        std::string username; // username of OrderBookEntry
};