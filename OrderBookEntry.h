#ifndef ORDERBOOKENTRY_H
#define ORDERBOOKENTRY_H
#pragma once
#include <string>

enum class OrderBookType{bid, ask, sale, unknown};

class OrderBookEntry{
    public:
        OrderBookEntry(
            double _price,
            double _amount,
            std::string _timestamp,
            std::string _product,
            OrderBookType _orderType);

        ~OrderBookEntry();

        static OrderBookType stringToOrderBookType(std::string s);

        static bool compareByTimestamp(const OrderBookEntry& e1, const OrderBookEntry& e2){
            return e1.timestamp < e2.timestamp;
        }

        static bool compareByPriceAscending(const OrderBookEntry& e1, const OrderBookEntry& e2){
            return e1.price < e2.price;
        }

        static bool compareByPriceDescending(const OrderBookEntry& e1, const OrderBookEntry& e2){
            return e1.price > e2.price;
        }

        std::string toString();

        std::string obtToString();

        double price;
        double amount;
        std::string timestamp;
        std::string product;
        OrderBookType orderType;

};
#endif