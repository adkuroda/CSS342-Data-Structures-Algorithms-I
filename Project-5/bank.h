//
//  bank.hpp
//  Project5 V2
//
//  Created by Adilet Kuroda on 11/28/22.
//

#ifndef BANK_H_
#define BANK_H_
#include <queue>
#include <fstream> 
#include "bstree.h"
#include "transaction.h"


class Bank{
public:
    Bank();
    void ParseText(const string& file_name);
    void ProcessTransaction();
    
    void Display() const;
    
//    void Display(){
//        cout << "deleter this " << endl;
//        while(!transactions_.empty()){
//            cout <<transactions_.front();
//            transactions_.pop();
//        }
//    }
    
    
private:
    queue<Transaction> transactions_;
    BSTree accounts_;
    
    bool Open(const Transaction& transaction);
    bool Deposit(Transaction& transaction,  Account*& account);
    bool Withdraw(Transaction& transaction, Account*& acct);
    bool Transfer(Transaction& transaction, Account*& acct);
    void ParserHelper(const string& line);
    bool DisplayAccountHistory(Transaction& transaction, Account*& acct) const;
    bool DisplayFundHistory(Transaction& transaction, Account*& acct) const;
    
    
};


#endif /* bank_hpp */
