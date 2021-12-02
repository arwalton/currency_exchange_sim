#ifndef MERKELMAIN_H
#define MERKELMAIN_H
#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
	
class MerkelMain  
{
	private:
		bool isRunning;
		OrderBook orderBook{"testData.csv"};

		void printMenu();
		int getUserOption();
		void printHelp();
		void printExchangeStats();
		void enterAsk();
		void makeBid();
		void printWallet();
		void advanceTimeframe();
		void printExitMessage();
		void handleBadInput();
		void processUserOption(int userOption);

		std::string currentTime;

	public:

		MerkelMain();
		~MerkelMain();
		void init();


};
#endif