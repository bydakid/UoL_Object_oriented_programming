#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <vector>
#include <string>

class OrderBook
{
    public:
        OrderBook(std::string filename); // constructor that takes a filename string as input and creates an OrderBook object
        std::vector<std::string> getKnownProducts(); // return a vector of strings
        // Returns a vector of OrderBookEntry objects that gives OrderBookType, product and timestamp
        std::vector<OrderBookEntry> getOrders(  OrderBookType type,
                                                std::string product,
                                                std::string timestamp);
        //Earliest time in the orderbook
        std::string getEarliestTime();
        //Next time in the orderbook
        std::string getNextTime(std::string timestamp);

        static double getHighPrice(std::vector<OrderBookEntry> & orders); // returns the highest price
        static double getLowPrice(std::vector<OrderBookEntry> & orders); // returns the lowest price
        static double getAvgPrice(std::vector<OrderBookEntry> & orders); // returns the average price
    private:
        std::vector<OrderBookEntry> orders; // vector of OrderBookEntry

};