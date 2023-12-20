//
//  transaction.hpp
//  Project5 V2
//
//  Created by Adilet Kuroda on 11/28/22.
//

#ifndef TRANSACTION_H_
#define TRANSACTION_H_
#include <string>
#include <iostream> 
using namespace std;

class Transaction{
public: 
    Transaction();

    bool SetOpen(string t_type, int account_base, string f_name, string l_name);
    bool SetDeposit(string t_type, int amount, int account_base, int fund_base);
    bool SetWithdraw(string t_type, int amount, int account_base, int fund_base);
    bool SetTransfer(string t_type, int amount, int account_base, int fund_base,
                     int account_receive, int fund_receive);
    bool SetDisplayAccountHistory(string t_type, int account_base);
    bool SetDisplayFundHistory(string t_type, int account_base, int fund_base);
    
    void DisplayDeposit() const;
    void DisplayWithdraw() const;
    void DisplayTransfer() const;
    
    
    string transaction_type() const;
    int amount() const;
    int account_base() const;
    int account_receive() const;
    int fund_base() const;
    int fund_receive() const;
    bool status() const;
    string f_name() const;
    string l_name() const;
    bool set_amount(int amount);
    bool set_status(bool status);

    
private:
    string transaction_type_;
    int amount_;
    int account_base_;
    int account_receive_;
    int fund_base_;
    int fund_receive_;
    bool status_;
    string f_name_;
    string l_name_;
    
};

#endif /* transaction_hpp */
