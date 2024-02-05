#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include <iterator>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <map>
#include <sstream>

// default constructor
MerkelMain::MerkelMain()
{
    
}

void MerkelMain::init()
{
    std::string input; // initialize the input string
    currentTime = orderBook.getEarliestTime(); // set the current time from the earliest time in orderbook
    while(true) // main loop
    {
        printIntro(); // print the intro message
        input = getUserOption(); // get user's input
        processUserOption(input); // process the user input
    }
}

// print intro text
void MerkelMain::printIntro()
{
    std::cout << "Please enter a command, or help for a list of commands" << std::endl; // print message
}

// print list of commands
void MerkelMain::printHelp()
{   
    std::cout << "Available commands are : help - prod - min - max - avg - time - step - square" << std::endl; // print message
}

// print list of products
void MerkelMain::printProd()
{   
    std::cout << "Available products are "; // print message
    for(std::string const p : orderBook.getKnownProducts()) // Iterate the list of products
    {
        std::cout << p << ", "; // print the product
    }
    std::cout << std::endl; // print a new line to move to next line
}

// print the min ask/bid of the products
void MerkelMain::printMin()
{
    for(std::string const p : orderBook.getKnownProducts()) // Iterate the list of products
    {
        std::vector<OrderBookEntry> askEntries = orderBook.getOrders(OrderBookType::ask, p, currentTime); // get the ask entries for the current product at the current time
        std::vector<OrderBookEntry> bidEntries = orderBook.getOrders(OrderBookType::bid, p, currentTime); // get the bid entries for the current product at the current time
        std::cout << "Min ask for " << p << " is " <<OrderBook::getLowPrice(askEntries)<<std::endl; // print min ask
        std::cout << "Min bid for " << p << " is " <<OrderBook::getLowPrice(bidEntries)<<std::endl; // print min bid
    }
}

// print the max ask/bid of the products
void MerkelMain::printMax()
{
    for(std::string const p : orderBook.getKnownProducts()) // Iterate the list of products
    {
        std::vector<OrderBookEntry> askEntries = orderBook.getOrders(OrderBookType::ask, p, currentTime); // get the ask entries for the current product at the current time
        std::vector<OrderBookEntry> bidEntries = orderBook.getOrders(OrderBookType::bid, p, currentTime); // get the bid entries for the current product at the current time
        std::cout << "Max ask for " << p << " is " <<OrderBook::getHighPrice(askEntries)<<std::endl; // print max ask
        std::cout << "Max bid for " << p << " is " <<OrderBook::getHighPrice(bidEntries)<<std::endl; // print max ask
    }
}

// print the average ask/bid of the products
void MerkelMain::printAvg()
{
    for(std::string const p : orderBook.getKnownProducts()) // Iterate the list of products
    {
        std::vector<OrderBookEntry> askEntries = orderBook.getOrders(OrderBookType::ask, p, currentTime); // get the ask entries for the current product at the current time
        std::vector<OrderBookEntry> bidEntries = orderBook.getOrders(OrderBookType::bid, p, currentTime); // get the bid entries for the current product at the current time
        std::cout << "Avg ask for " << p << " is " <<OrderBook::getAvgPrice(askEntries)<<std::endl; // print avg ask
        std::cout << "Avg bid for " << p << " is " <<OrderBook::getAvgPrice(bidEntries)<<std::endl; // print avg bid
    }
}

// print the current time
void MerkelMain::printTime()
{   
    std::cout << "Time : " << currentTime << std::endl; // time message
}

// print the next timestamp
void MerkelMain::printStep()
{
    currentTime = orderBook.getNextTime(currentTime); // increment the time to the next time step
    std::cout << "New Time : " << currentTime << std::endl; // time message
}

// print the square calculation
void MerkelMain::printSquare()
{
    std::cout << "Enter a number: "; // user input a number
    int num; // read the input as an integer
    std::cin >> num;
    std::cout << "The square of " << num << " is " << num * num << std::endl; // print the result with the calculated number
}

// the input command that will return the input as a string
std::string MerkelMain::getUserOption()
{ 
    std::string userInput; // initialize the input string
    std::cin >> userInput; // read a string
    return userInput; // return the string
}

// processes the user input and calls the function
void MerkelMain::processUserOption(const std::string& userInput)
{
    // if the input is "help"
    if (userInput == "help")
    {
        printHelp(); // call the function
        std::cout << "=====================================================================================================" << std::endl;
    }
    // if the input is "prod"
    else if (userInput == "prod")
    {
        printProd(); // call the function
        std::cout << "=====================================================================================================" << std::endl;
    }
    // if the input is "min"
    else if (userInput == "min")
    {
        printMin(); // call the function
        std::cout << "=====================================================================================================" << std::endl;
    }
    // if the input is "max"
    else if (userInput == "max")
    {
        printMax(); // call the function
        std::cout << "=====================================================================================================" << std::endl;
    }
    // if the input is "avg"
    else if (userInput == "avg")
    {
        printAvg(); // call the function
        std::cout << "=====================================================================================================" << std::endl;
    }
    // if the input is "time"
    else if (userInput == "time")
    {
        printTime(); // call the function
        std::cout << "=====================================================================================================" << std::endl;
    }
    // if the input is "step"
    else if (userInput == "step")
    {
        printStep(); // call the function
        std::cout << "=====================================================================================================" << std::endl;
    }
    // if the input is "square"
    else if (userInput == "square")
    {
        printSquare(); // call the function
        std::cout << "=====================================================================================================" << std::endl;
    }
    // the rest type of input
    else
    {
        std::cout << "ERROR!! Invalid command. Type the exact command from the list provided." << std::endl; // print message
        std::cout << "=====================================================================================================" << std::endl;
    }
}
