#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <limits>
	
MerkelMain::MerkelMain()
{
	isRunning = true;
}
	
MerkelMain::~MerkelMain()
{

}

/** Call this to start the simulation */
void MerkelMain::init(){
    int input;
    currentTime = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC",10);
    while(isRunning){
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::printMenu(){
    // 1 print help
    std::cout << "1: Print help" << std::endl;
    // 2 print exchange stats
    std::cout << "2: Print exchange stats" << std::endl;
    // 3 make and offer
    std::cout << "3: Make an ask" << std::endl;
    // 4 make a bid
    std::cout << "4: Make a bid" << std::endl;
    // 5 print wallet
    std::cout << "5: Print wallet" << std::endl;
    // 6 continue
    std::cout << "6: Continue" << std::endl;
    // 7 exit
    std::cout << "7: Exit the program" << std::endl;

    std::cout << "Current time is: " << currentTime << std::endl;

    std::cout << "==================" << std::endl;
}

int MerkelMain::getUserOption(){
    int userOption = 0;
    std::string line;
    std::cout << "Type in 1-7" << std:: endl << std::endl;
    std::getline(std::cin, line);
    try{
        userOption = std::stoi(line);
    }catch(const std::exception& e){
        //
    }
    std::cout << std::endl << "You chose: " << userOption << std::endl << std::endl;
    return userOption;
}

void MerkelMain::printHelp(){
    std::cout << "Help - your aim is to make money. Analyze the market and make bids and offers" << std::endl << std::endl;
}

void MerkelMain::printExchangeStats(){

    for(std::string const& p : orderBook.getKnownProducts()){
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> askEntries = 
            orderBook.getOrders(OrderBookType::ask, p, currentTime);
        std::cout << "Asks seen: " << askEntries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(askEntries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(askEntries) << std::endl;
        std::cout << "Mean price per unit ask: " << OrderBook::getMeanPPU(askEntries) << std::endl;
        std::cout << "Standard Deviation ask: " << OrderBook::getStDevPPU(askEntries) << std::endl << std::endl;

        std::vector<OrderBookEntry> bidEntries = 
            orderBook.getOrders(OrderBookType::bid, p, currentTime);
        std::cout << "Bids seen: " << bidEntries.size() << std::endl;
        std::cout << "Max bid: " << OrderBook::getHighPrice(bidEntries) << std::endl;
        std::cout << "Min bid: " << OrderBook::getLowPrice(bidEntries) << std::endl;
        std::cout << "Mean price per unit bid: " << OrderBook::getMeanPPU(bidEntries) << std::endl;
        std::cout << "Standard Deviation bid: " << OrderBook::getStDevPPU(bidEntries) << std::endl << std::endl;

    }
}

void MerkelMain::enterAsk(){
    std::cout << "Make an ask. Enter the amount: product,price,amount, eg ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    
    std::vector<std::string> tokens = CSVReader::tokenise(input,',');
    if(tokens.size() != 3){
        std::cout << "MerkelMain::enterAsk Bad input! " << input << std::endl;

    }else{
        try{
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::ask
            );
            obe.username = "simuser";
            if(wallet.canFulfillOrder(obe)){
                std::cout << "The wallet can cover this order." << std::endl;
                orderBook.insertOrder(obe);
                std::cout << "Your order has been added to the orderBook." << std::endl;
                std::cout << "Order summary:" << std::endl;
                std::cout << obe << std::endl << std::endl;
            }else{
                std::cout << "The wallet has insufficient funds to cover this order." <<
                std::endl << "Try checking your balances and resubmitting." << std::endl << std:: endl;
            }

        }catch (const std::exception& e){
            std::cout << "MerkelMain::enterAsk bad input!" << std::endl;
        }
    }
}

void MerkelMain::makeBid(){
    std::cout << "Make a bid. Enter the amount: product,price,amount, eg ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    
    std::vector<std::string> tokens = CSVReader::tokenise(input,',');
    if(tokens.size() != 3){
        std::cout << "MerkelMain::makeBid Bad input! " << input << std::endl;

    }else{
        try{
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::bid
            );
            obe.username = "simuser";
            if(wallet.canFulfillOrder(obe)){
                std::cout << "The wallet can cover this order." << std::endl;
                orderBook.insertOrder(obe);
                std::cout << "Your order has been added to the orderBook." << std::endl;
                std::cout << "Order summary:" << std::endl;
                std::cout << obe << std::endl << std::endl;
            }else{
                std::cout << "The wallet has insufficient funds to cover this order." <<
                std::endl << "Try checking your balances and resubmitting." << std::endl << std:: endl;
            }
        }catch (const std::exception& e){
            std::cout << "MerkelMain::makeBid bad input!" << std::endl;
        }
    }
}

void MerkelMain::printWallet(){
    std::cout << "Current Balances: " << std::endl << wallet << std::endl;
}

void MerkelMain::advanceTimeframe(){
    std::cout << "Going to next timeframe" << std::endl << std::endl;
    for(std::string& p : orderBook.getKnownProducts()){
        std::cout << "****Matching " << p << "****" << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        std::cout << "User sales:" << std::endl << std::endl;

        for(OrderBookEntry& sale : sales){
            if(sale.username == "simuser"){
                //Update the wallet
                wallet.processSale(sale);
                std::cout << sale << std::endl << std::endl;
            }
        }
    }

    currentTime = orderBook.getNextTime(currentTime);
}

void MerkelMain::printExitMessage(){
    std::cout << "Thanks for playing! Goodbye." << std::endl;
}

void MerkelMain::handleBadInput(){
    std::cout << "Invalid choice. Choose 1-7" << std::endl << std::endl;
}

void MerkelMain::processUserOption(int userOption){
    if(userOption == 1){ //Help
        printHelp();
    }else if(userOption == 2){ //Print exchange stats
        printExchangeStats();
    }else if(userOption == 3){ //Make offer
        enterAsk();
    }else if(userOption == 4){ //Make bid
        makeBid();
    }else if(userOption == 5){ //Print wallet
        printWallet();
    }else if(userOption == 6){ //Continue
        advanceTimeframe();
    }else if(userOption == 7){ //Exit the game
        printExitMessage();
    }else{
        handleBadInput();
    }
    if(userOption == 7){
        isRunning = false;
    }
}