

#include "account.h"

Account::Account(const int& id, const string& f_name, const string& l_name){
    account_id_ = id;
    customer_ = Customer(f_name, l_name);
    for(int i = 0; i < 8; i++){
        Fund fund(FUNDS[i], i);
        funds_.push_back(fund);
    }
}
Account::Account(const Account& account){
    *this = account;
}

int Account::account_id() const{
    return account_id_;
}
vector<Fund>& Account::funds(){
    return funds_;
}

Customer Account::customer() const{
    return customer_;
}
void Account::DisplayAllFundHistory() const{
    cout << "Transaction History for "<< customer() << "by fund." << endl;
    for(int i = 0; i < static_cast<int>(funds_.size()); i++){
        funds_[i].DisplayFundHistory();
    }
}

Account& Account::operator = (const Account& rhs){
    account_id_ = rhs.account_id_;
    customer_ = rhs.customer_;
    for (int i = 0; i <static_cast<int>(rhs.funds_.size()); i++){
        funds_.push_back(rhs.funds_[i]);
    }
    return *this;
}


bool Account::operator == (const Account& rhs) const{
    return account_id_ == rhs.account_id_;
}
bool Account::operator != (const Account& rhs) const{
    return account_id_ != rhs.account_id_;
}
bool Account::operator > (const Account& rhs) const{
    return account_id_ > rhs.account_id_;
}
bool Account::operator >= (const Account& rhs) const{
    return account_id_ >= rhs.account_id_;
}
bool Account::operator < (const Account& rhs) const{
    return account_id_ < rhs.account_id_;
}
bool Account::operator <= (const Account& rhs) const{
    return account_id_ <= rhs.account_id_;
}


ostream& operator<< (ostream& os, const Account& rhs){
    os<< rhs.customer_ << "Account ID: "<<rhs.account_id_ << endl;
    for(int i = 0; i < static_cast<int>(rhs.funds_.size()); i++){
        os << rhs.funds_[i];
    }
    os << endl;
    return os;
}
