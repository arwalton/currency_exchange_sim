#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"
	
MerkelMain::MerkelMain()
{
	isRunning = true;
}
	
MerkelMain::~MerkelMain()
{

}

/** Call this to start the simulation */
void MerkelMain::init(){
    loadOrderBook();
    int input;
    while(isRunning){
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::loadOrderBook(){
    
    orders = CSVReader::readCSV("20200317.csv");
        
}

void MerkelMain::printMenu(){
    // 1 print help
    std::cout << "1: Print help" << std::endl;
    // 2 print exchange stats
    std::cout << "2: Print exchange stats" << std::endl;
    // 3 make and offer
    std::cout << "3: Make an offer" << std::endl;
    // 4 make a bid
    std::cout << "4: Make a bid" << std::endl;
    // 5 print wallet
    std::cout << "5: Print wallet" << std::endl;
    // 6 continue
    std::cout << "6: Continue" << std::endl;
    // 7 exit
    std::cout << "7: Exit the program" << std::endl;

    std::cout << "==================" << std::endl;
}

int MerkelMain::getUserOption(){
    int userOption;
    std::cout << "Type in 1-7" << std:: endl;
    std::cin >> userOption;
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

void MerkelMain::printHelp(){
    std::cout << "Help - your aim is to make money. Analyze the market and make bids and offers" << std::endl;
}

void MerkelMain::printExchangeStats(){
    std::cout << "OrderBook contains : " << orders.size() << " entries." << std::endl;
    unsigned int bids = 0;
    unsigned int asks = 0;
    for (OrderBookEntry& e : orders){
        if(e.orderType == OrderBookType::ask){
            asks++;
        }
        if(e.orderType == OrderBookType::bid){
            bids++;
        }
    }

    std::cout << "OrderBook asks: " << asks << std::endl;
    std::cout << "OrderBook bids: " << bids << std::endl;

}

void MerkelMain::makeOffer(){
    std::cout << "Make an offer. Enter the amount" << std::endl;
}

void MerkelMain::makeBid(){
    std::cout << "Make a bid. enter the amount" << std::endl;
}

void MerkelMain::printWallet(){
    std::cout << "Your wallet is empty" << std::endl;
}

void MerkelMain::advanceTimeframe(){
    std::cout << "Going to next timeframe" << std::endl;
}

void MerkelMain::printExitMessage(){
    std::cout << "Thanks for playing! Goodbye." << std::endl;
}

void MerkelMain::handleBadInput(){
    std::cout << "Invalid choice. Choose 1-7" << std::endl;
}

void MerkelMain::processUserOption(int userOption){
    if(userOption == 1){ //Help
        printHelp();
    }else if(userOption == 2){ //Print exchange stats
        printExchangeStats();
    }else if(userOption == 3){ //Make offer
        makeOffer();
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