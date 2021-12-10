#ifndef WALLET_H
#define WALLET_H
#pragma once

#include <string>
#include <map>
#include "OrderBookEntry.h"
	
class Wallet  
{
	private:
		std::map<std::string,double> currencies;

	public:

		Wallet();
		~Wallet();

		/**
		 * @brief Insert currency into the wallet
		 * 
		 * @param type The type of currency
		 * @param amount How much of the currency to insert
		 */
		void insertCurrency(std::string type, double amount);

		/**
		 * @brief Remove currency from the wallet.
		 * 
		 * @param type The type of currency
		 * @param amount How much of the currency to remove
		 * @return true The currency was removed successfully
		 * @return false That amount of currency was unable to be removed
		 */
		bool removeCurrency(std::string type, double amount);

		/**
		 * @brief Check if the wallet contains this much currency or more
		 * 
		 * @param type The type of currency
		 * @param amount The amount of currency we're looking for.
		 * @return true The wallet contains at least that amount of the chosen currency
		 * @return false The wallet does not contain that amount of the chosen currency
		 */
		bool containsCurrency(std::string type, double amount);

		/**
		 * @brief Determines whether there is enough money in the wallet to fullill the order
		 * 
		 * @param order The OrderBookEntry we are testing
		 * @return true There is enough currency to place this order
		 * @return false There is not enough currency to place this order
		 */
		bool canFulfillOrder(OrderBookEntry& order);

		/**
		 * @brief Updates the contents of the wallet. Assumes that the order
		 * was made by the user.
		 * 
		 * @param sale the OrderBookEntry containing the sale
		 */
		void processSale(OrderBookEntry& sale);

		/**
		 * @brief Generate a string representation of the wallet
		 * 
		 * @return std::string 
		 */
		std::string toString();

		/**
		 * @brief Allows the wallet to stream to ostream.
		 * 
		 * @param os 
		 * @param wallet 
		 * @return std::ostream& 
		 */
		friend std::ostream& operator<<(std::ostream& os, Wallet& wallet);

};
#endif