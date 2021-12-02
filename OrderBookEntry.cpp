#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(
    double _price,
    double _amount,
    std::string _timestamp,
    std::string _product,
    OrderBookType _orderType
)
: price(_price),
  amount(_amount),
  timestamp(_timestamp),
  product(_product),
  orderType(_orderType)
{
    
}

OrderBookEntry::~OrderBookEntry(){

}

OrderBookType OrderBookEntry::stringToOrderBookType(std::string s){
    if(s == "ask"){
        return OrderBookType::ask;
    }
    if(s == "bid"){
        return OrderBookType::bid;
    }
    return OrderBookType::unknown;
}

std::string OrderBookEntry::toString(){
    std::string entry = "";
    entry = entry + "price: " + std::to_string(price) + "\n";
    entry = entry + "amount: " + std::to_string(amount) + "\n";
    entry = entry + "timestamp: " + timestamp + "\n";
    entry = entry + "product: " + product + "\n";
    entry = entry + "ordertype: " + obtToString() + "\n";
    
    return entry;
}

std::string OrderBookEntry::obtToString(){
    if(orderType == OrderBookType::ask){
        return "ask";
    }else if(orderType == OrderBookType::bid){
        return "bid";
    }else{
        return "unknown";
    }
}