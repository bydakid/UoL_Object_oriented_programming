#include "OrderBookEntry.h"

// constructor for the OrderBookEntry class
OrderBookEntry::OrderBookEntry( double _price,
                                double _amount,
                                std::string _currenTime,
                                std::string _product,
                                OrderBookType _orderType)
:   price(_price),
    amount(_amount),
    currenTime(_currenTime),
    product(_product),
    orderType(_orderType)
{

}

// method that takes a string as input and returns an OrderBookType
OrderBookType OrderBookEntry::stringToOrderBookType(std::string s)
{
   if (s == "ask") // if string is "ask"
   {
    return OrderBookType::ask; // return ask
   } 
   if (s == "bid") // if string is "bid"
   {
    return OrderBookType::bid; // return bid
   }
   return OrderBookType::unknown; // return unknown
}