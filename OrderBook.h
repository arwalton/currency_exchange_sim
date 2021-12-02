#ifndef ORDERBOOK_H
#define ORDERBOOK_H
#pragma once

#include "OrderBookEntry.h"
#include <string>
#include <vector>
	
class OrderBook  
{
	private:
		std::vector<OrderBookEntry> orders;

	public:

		/**
		 * @brief Construct a new Order Book object
		 * 
		 * @param filename - the path to a cvs file
		 */
		OrderBook(std::string filename);
		~OrderBook();

		/**
		 * @brief Return a vector of all known products in the
		 * dataset.
		 * 
		 * @return std::vector<std::string> 
		 */
		std::vector<std::string> getKnownProducts();

		/**
		 * @brief return a vector of orders according to the 
		 * sent filters.
		 * 
		 */
		std::vector<OrderBookEntry> getOrders(OrderBookType type,
											std::string product,
											std::string timestamp);

		/**
		 * @brief inserts an OrderBookEntry into the OrderBook
		 * 
		 * @param order an OrderBookEntry
		 */
		void insertOrder(OrderBookEntry& order);

		/**
		 * @brief Gets the earliest time in our data.
		 * 
		 * @return std::string 
		 */
		std::string getEarliestTime();

		/**
		 * @brief Returns the next time after the sent time in
		 * the OrderBook. If there is no next timestamp
		 * it wraps around back to the starting time.
		 * 
		 * @param timestamp a string representing a timestamp
		 * @return std::string 
		 */
		std::string getNextTime(std::string timestamp);


		/**
		 * @brief Get the highest price in a vector of orders
		 * 
		 * @param orders vector of OrderBookEntry
		 * @return The highest price 
		 */
		static double getHighPrice(std::vector<OrderBookEntry>& orders);

		/**
		 * @brief Get the lowest price in a vector of orders
		 * 
		 * @param orders vector of OrderBookEntry
		 * @return The lowest price 
		 */		
		static double getLowPrice(std::vector<OrderBookEntry>& orders);

		/**
		 * @brief Get the mean prixe per unit of a vector of OrderBookEntry
		 * 
		 * @param orders a vector of OrderBookEntry
		 * @return a double representing the mean value 
		 */
		static double getMeanPPU(std::vector<OrderBookEntry>& orders);

		/**
		 * @brief Get the standard deviation per unit of a vector of OrderBookEntry
		 * 
		 * @param orders a vector of OrderBookEntry
		 * @return double representing the standard deviation per unit
		 */
		static double getStDevPPU(std::vector<OrderBookEntry>& orders);

		/**
		 * @brief Matches asks and bids and returns the resulting vector of sales
		 * 
		 * @return std::vector<OrderBookEntry> a vector of OrderBookEntrys of sales 
		 */
		std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);
};
#endif