#ifndef MERKELMAIN_H
#define MERKELMAIN_H
#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"
	
class MerkelMain  
{
	private:
		bool isRunning;
		OrderBook orderBook{"20200317.csv"};
		std::string currentTime;
		Wallet wallet;

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

	public:

		MerkelMain();
		~MerkelMain();
		void init();


};
#endif