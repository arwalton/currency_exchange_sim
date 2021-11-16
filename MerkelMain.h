#ifndef MERKELMAIN_H
#define MERKELMAIN_H
#pragma once
#include <vector>
#include "OrderBookEntry.h"
	
class MerkelMain  
{
	private:
		bool isRunning;
		std::vector<OrderBookEntry> orders;

		void loadOrderBook();
		void printMenu();
		int getUserOption();
		void printHelp();
		void printExchangeStats();
		void makeOffer();
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