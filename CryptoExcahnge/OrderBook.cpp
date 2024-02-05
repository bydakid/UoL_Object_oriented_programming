#include "OrderBook.h"
#include "CSVReader.h"
#include <map>

OrderBook::OrderBook(std::string filename)
{
     // initialize the orders member variable by calling the readCSV static method of the CSVReader class
    orders = CSVReader::readCSV(filename);
}

//return a vector of strings of products of the OrderBook
std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products; // initialize an empty vector string

    std::map<std::string,bool> prodMap; // initialize an empty map
    //iterate over the orders and add each product to the map
    for (OrderBookEntry& e : orders)
    {
        prodMap[e.product] = true;
    }
    //iterate over prodMap and add each key
    for (auto const& e : prodMap)
    {
        products.push_back(e.first);
    }

    return products; // return products
}

//return a vector of OrdrBookEntry
std::vector<OrderBookEntry> OrderBook::getOrders(   OrderBookType type,
                                                    std::string product,
                                                    std::string timestamp)
{
    std::vector<OrderBookEntry> orders_sub; // initialize an empty vector
    //iterate over the orders
    for (OrderBookEntry& e : orders)
    {
        // if e. matches type, product and timestamp
        if( e.orderType == type &&
            e.product == product &&
            e.currenTime == timestamp)
            {
                orders_sub.push_back(e); // add OrderBookEntry to order_sub 
            }
    }
    return orders_sub; // return orders_sub
}

// returns the highest price
double OrderBook::getHighPrice(std::vector<OrderBookEntry> & orders)
{
    double max = orders[0].price; // initialize the max variable to the price
    // iterate over the orders
    for (OrderBookEntry& e : orders)
    {
        if(e.price > max)max = e.price; // if price is greater than max, update max of the price member variable
    }
    return max; // return max price
}

// returns the lowest price
double OrderBook::getLowPrice(std::vector<OrderBookEntry> & orders)
{
    double min = orders[0].price;// initialize the min variable to the price
    // iterate over the orders
    for (OrderBookEntry& e : orders)
    {
        if(e.price < min)min = e.price; // if price is smaller than min, update min of the price member variable
    }
    return min; // return minimum price
}

// returns the average price
double OrderBook::getAvgPrice(std::vector<OrderBookEntry> & orders)
{
  double totalPrice = orders[0].price; // initialize the totalPrice variable to the price
    // iterate over the orders
  for (OrderBookEntry& e : orders) {
    totalPrice += e.price; // add price of OrderBookEntry to the totalPrice
  }
  return totalPrice / orders.size(); // return totalPrice 
}

// return the earliest timestamp
std::string OrderBook::getEarliestTime()
{
    return orders[0].currenTime; // return the first variable in the currentime
}

// return the next timestamp
std::string OrderBook::getNextTime(std::string timestamp)
{
    std::string next_timestamp = ""; // empty string to store the next timestamp
    // iterate over the orders
    for (OrderBookEntry& e : orders)
    {
        // if currentime is bigger than timestamp
        if (e.currenTime > timestamp)
        {
            next_timestamp = e.currenTime; // update next_timestamp
            break; // break the loop
        }
    }
    // if next_timestamp is an empty string
    if (next_timestamp == "")
    {
        next_timestamp = orders[0].currenTime; // set next_timestamp to the currentime
    }
    return next_timestamp; // return the next_timestamp
}


