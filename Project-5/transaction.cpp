#include "transaction.h"

Transaction::Transaction(){
    transaction_type_ ="";
    f_name_ = "";
    l_name_ = "";
    amount_ = 0;
    account_base_ = 0;
    account_receive_ = 0;
    fund_base_ = 0;
    fund_receive_ = 0;
    status_ = false;
}

int Transaction::amount() const{
    return amount_;
}
int Transaction::account_base() const{
    return account_base_;
}
int Transaction::account_receive() const{
    return account_receive_;
}
int Transaction::fund_base() const{
    return fund_base_;
}
int Transaction::fund_receive() const{
    return fund_receive_;
}
bool Transaction::status() const{
    return status_;
}
string Transaction::f_name() const{
    return f_name_;
}
string Transaction::l_name() const{
    return l_name_;
}

bool Transaction::SetOpen(string t_type, int account_base, string f_name, string l_name){
    transaction_type_ = t_type;
    l_name_ = l_name;
    f_name_ = f_name;
    account_base_ = account_base;
    return true;
}
bool Transaction::SetDeposit(string t_type, int amount, int account_base, int fund_base){
    transaction_type_ = t_type;
    amount_ = amount;
    account_base_ = account_base;
    fund_base_ = fund_base;
    return true;
}
bool Transaction::SetWithdraw(string t_type, int amount, int account_base, int fund_base){
    transaction_type_ = t_type;
    amount_ = amount;
    account_base_ = account_base;
    fund_base_ = fund_base;
    return true;
}
bool Transaction::SetTransfer(string t_type, int amount, int account_base, int fund_base,
                              int account_receive, int fund_receive){
    transaction_type_ = t_type;
    amount_ = amount;
    account_base_ = account_base;
    fund_base_ = fund_base;
    fund_receive_ = fund_receive;
    account_receive_ = account_receive;
    return true;
}
bool Transaction::SetDisplayAccountHistory(string t_type, int account_base){
    transaction_type_ = t_type;
    account_base_ = account_base;
    return true;
}
bool Transaction::SetDisplayFundHistory(string t_type, int account_base, int fund_base){
    transaction_type_ = t_type;
    account_base_ = account_base;
    fund_base_ = fund_base;
    return true;
}
string Transaction::transaction_type() const{
    return transaction_type_;
}
bool Transaction::set_amount(int amount){
    amount_ = amount;
    return true;
}
bool Transaction::set_status(bool status){
    status_ = status;
    return true;
}
void Transaction::DisplayDeposit() const{
    cout << "  " << transaction_type_;
    cout << " " <<account_base_;
    cout << " " <<fund_base_;
    cout << " " <<amount_;
    if (!status_){
        cout << " (Failed)" << endl;
    }else{
        cout << endl;
    }
}
void Transaction::DisplayWithdraw() const{
    cout << "  " << transaction_type_;
    cout << " " << account_base_;
    cout << " " << fund_base_;
    cout << " " << amount_;
    if (!status_){
        cout << " (Failed)" << endl;
    }else{
        cout << endl;
    }
}
void Transaction::DisplayTransfer() const{
    cout << "  " << transaction_type_;
    cout << " " << account_base_;
    cout << " " << fund_base_;
    cout << " " << account_receive_;
    cout << " " << fund_receive_;
    cout << " " << amount_;
    if (!status_){
        cout << " (Failed)" << endl;
    }else{
        cout << endl;
    }
}


