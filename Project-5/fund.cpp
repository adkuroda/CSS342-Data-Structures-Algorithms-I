
#include "fund.h"

Fund::Fund(const string& fund_type, int id){
    fund_type_ = fund_type;
    fund_id_ = id;
    amount_ = 0;
}
void Fund::AddFund(int amount){
    amount_ += amount;
}
int Fund::amount() const{
    return amount_;
}
string Fund::fund_type() const{
    return fund_type_;
}

void Fund::DisplayFundHistory() const{
    if (history_.size() != 0){
        cout << fund_type_ <<": $" << amount_ << endl;
    }
    for(int i = 0; i < static_cast<int>(history_.size()); i++){
        if(history_[i].transaction_type() == "D"){
            history_[i].DisplayDeposit();
        }
        else if(history_[i].transaction_type() == "T"){
            history_[i].DisplayTransfer();
        }
        else if(history_[i].transaction_type() == "W"){
            history_[i].DisplayWithdraw();
        }else{
            continue;
        }
    }
}

void Fund::AddHistory(const Transaction& transaction){
    history_.push_back(transaction);
}

ostream& operator<<(ostream& os, const Fund& rhs){
    os <<"    " << rhs.fund_type_ <<": $" << rhs.amount_ << endl;
    return os;
}
