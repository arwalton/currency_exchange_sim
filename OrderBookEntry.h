#ifndef ORDERBOOKENTRY_H
#define ORDERBOOKENTRY_H
#pragma once
#include <string>

enum class OrderBookType{bid, ask};

class OrderBookEntry{
    public:
        OrderBookEntry(
            double _price,
            double _amount,
            std::string _timestamp,
            std::string _product,
            OrderBookType _orderType);
        
        ~OrderBookEntry();

        double price;
        double amount;
        std::string timestamp;
        std::string product;
        OrderBookType orderType;

};
#endif