#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
private:
    std::string id_;
    std::string sender_;
    std::string receiver_;
    double amount_;

public:
    Transaction(const std::string& id, 
                const std::string& sender,
                const std::string& receiver,
                double amount);
    
    std::string toString() const;
    std::string toHash() const;
    
    const std::string& getId() const { return id_; }
    const std::string& getSender() const { return sender_; }
    const std::string& getReceiver() const { return receiver_; }
    double getAmount() const { return amount_; }
    
    void print() const;
};

#endif