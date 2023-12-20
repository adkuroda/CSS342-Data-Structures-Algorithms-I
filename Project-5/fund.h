
#ifndef FUND_H_
#define FUND_H_
#include "transaction.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Fund{
public:
    Fund(const string& fund_type, int id);
    void DisplayFundHistory() const;
    void AddFund(int amount);
    void AddHistory(const Transaction& transaction);
    int amount() const;
    string fund_type() const;
private:
    string fund_type_;
    int fund_id_;
    int amount_;
    vector<Transaction> history_;
    friend ostream& operator<<(ostream& os, const Fund& rhs);
};


#endif /* fund_hpp */
