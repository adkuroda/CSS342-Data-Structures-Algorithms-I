
#include "bank.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

Bank::Bank(){}
/** Parses the text: makes sure file name is correct 
 * Main marking occurs at ParseHelper 
*/
void Bank::ParseText(const string& file_name){
    fstream in_file;
    in_file.open(file_name);
    if (!in_file.is_open()){
        cerr << "Error: Wrong FileName" << endl;
        return;
    }
    string str;
    while(getline(in_file, str)){
        ParserHelper(str);
    }
}
/** Parse each line of the text and creates transaction 
 * object. Then inserted into a queue. 
*/
void Bank::ParserHelper(const string& line){
    string transaction_type;
    int amount;
    int account_base;
    int account_receive;
    int fund_base;
    int fund_receive;
    string f_name;
    string l_name;
    stringstream ss(line);
    ss >> transaction_type;
    Transaction temp;
    if (transaction_type == "O"){
        ss >> account_base >> f_name >> l_name;
        if (account_base < 0){
            cerr << "Error: Account # should be positive" << endl;
            return;
        }
        temp.SetOpen(transaction_type, account_base, f_name, l_name);
    }
    if(transaction_type == "D"){
        ss >> account_base >> fund_base >> amount;
        if (fund_base < 0 || fund_base > 7){
            cerr << "Error: Not Valid Fund ID" << endl;
            return;
        }
        if (amount < 0){
            cerr << "ERROR: Negative amount. Transaction refused" << endl;
            return;
        }

        temp.SetDeposit(transaction_type, amount, account_base, fund_base);
    }
    if(transaction_type == "W"){
        ss >> account_base >> fund_base >> amount;
        if (fund_base < 0 || fund_base > 7){
            cerr << "Error: Not Valid Fund ID" << endl;
            return;
        }
        if (amount < 0){
            cerr << "ERROR: Negative amount. Transaction refused" << endl;
            return;
        }
        temp.SetWithdraw(transaction_type, amount, account_base, fund_base);
    }
    if(transaction_type == "T"){
        ss >> account_base >> fund_base >> account_receive;
        ss >> fund_receive >> amount;
        if (fund_base < 0 || fund_base > 7){
            cerr << "Error: Not Valid Fund ID" << endl;
            return;
        }
        if (fund_receive < 0 || fund_receive > 7){
            cerr << "Error: Not Valid Fund ID" << endl;
            return;
        }
         if (amount < 0){
            cerr << "ERROR: Negative amount. Transaction refused" << endl;
            return;
        }
        temp.SetTransfer(transaction_type, amount, account_base,
                         fund_base, account_receive, fund_receive);
    }
    if(transaction_type == "F"){
        ss >> account_base >> fund_base;
        temp.SetDisplayFundHistory(transaction_type, account_base, fund_base);
    }
    if(transaction_type == "A"){
        ss >> account_base;
        temp.SetDisplayAccountHistory(transaction_type, account_base);
    }
    transactions_.push(temp);
}

// Goes through queue and executes each transactions by utilizing each 
// different functions what does specific transaciton like open or deposit. 
void Bank::ProcessTransaction(){
    while(!transactions_.empty()){
        Account * account = nullptr;
        Transaction temp = transactions_.front();
        if (temp.transaction_type() == "O"){
            Open(temp);
            transactions_.pop();
            continue;
        }
        accounts_.Retrieve(temp.account_base(), account);
        if (account == nullptr){
            cerr << "ERROR: Account "  << temp.account_base();
            cerr << " not found. Transaction refused."<< endl;
            transactions_.pop();
            continue;
        }
        if (account != nullptr){
            if(temp.amount() < 0){
                (*account).funds()[temp.fund_base()].AddHistory(temp);
                cerr << "ERROR: Requested amount is not valid" << endl;
                transactions_.pop();
                continue;
            }
            if (temp.transaction_type() == "D"){
                Deposit(temp, account);
            }
            if (temp.transaction_type() == "W"){
                Withdraw(temp, account);
            }
            if (temp.transaction_type() == "T"){
                Transfer(temp, account);
            }
            if (temp.transaction_type() == "A"){
                DisplayAccountHistory(temp, account);
            }
            if (temp.transaction_type() == "F"){
                DisplayFundHistory(temp, account);
            }
        }
        transactions_.pop();
    }
}

bool Bank::Open(const Transaction& t){
    Account* in_account;
    in_account = new Account(t.account_base(), t.f_name(), t.l_name());
    if (!accounts_.Insert(in_account)){
        delete in_account;
        cerr << "ERROR: Account "  << t.account_base();
        cerr << " is already open. Transaction refused."<< endl;
        return false;
    }
    return true;
}

/* Handles deposits */
bool Bank::Deposit(Transaction& t, Account*& acct){
    (*acct).funds()[t.fund_base()].AddFund(t.amount());
    t.set_status(true);
    (*acct).funds()[t.fund_base()].AddHistory(t);
    return true;
}

/* handles withraw transaction Sorry I did not get a chance to 
 * refactor the code. It is bit long  */
bool Bank::Withdraw(Transaction& t, Account*& acct){
    int fund_amount = (*acct).funds()[t.fund_base()].amount();
    if (fund_amount >= t.amount()){
        (*acct).funds()[t.fund_base()].AddFund(-t.amount());
        t.set_status(true);
        (*acct).funds()[t.fund_base()].AddHistory(t);
        return true;
        
        
    }else{
        int fund_0 = (*acct).funds()[0].amount();
        int fund_1 = (*acct).funds()[1].amount();
        int fund_2 = (*acct).funds()[2].amount();
        int fund_3 = (*acct).funds()[3].amount();
        if ((t.fund_base() == 0 || t.fund_base() == 1) && (fund_0 + fund_1) >= t.amount()){
            Transaction temp;
            int base;
            int amount;
            if (t.fund_base() == 0){
                base = 1;
                amount = t.amount() - fund_0;
            }else{
                base = 0;
                amount = t.amount() - fund_1;
            }
            t.set_amount(t.amount() - amount);
            (*acct).funds()[t.fund_base()].AddFund(-t.amount());
            t.set_status(true);
            (*acct).funds()[t.fund_base()].AddHistory(t);
            // add second history
            temp.SetWithdraw("W", amount, t.account_base(), base);
            (*acct).funds()[temp.fund_base()].AddFund(-temp.amount());
            temp.set_status(true);
            (*acct).funds()[temp.fund_base()].AddHistory(temp);
            return true;
        }
        if ((t.fund_base() == 2 || t.fund_base() == 3) && (fund_2 + fund_3) >= t.amount()){
            Transaction temp;
            int base;
            int amount;
            if (t.fund_base() == 2){
                base = 3;
                amount = t.amount() - fund_2;
            }else{
                base = 2;
                amount = t.amount() - fund_3;
            }
            t.set_amount(t.amount() - amount);
            (*acct).funds()[t.fund_base()].AddFund(-t.amount());
            t.set_status(true);
            (*acct).funds()[t.fund_base()].AddHistory(t);
            // add second history
            temp.SetWithdraw("W", amount, t.account_base(), base);
            (*acct).funds()[temp.fund_base()].AddFund(-temp.amount());
            temp.set_status(true);
            (*acct).funds()[temp.fund_base()].AddHistory(temp);
            return true;
 
        }
        (*acct).funds()[t.fund_base()].AddHistory(t);
        cerr << "ERROR: Not enough funds to withdraw " << t.amount();
        cerr << " from "  << (*acct).customer();
        cerr << (*acct).funds()[t.fund_base()].fund_type() << endl;
        return false;
        
    }
}
/* Handles Transfer: Sorry I did not get a chance to refactor the code
 * It bit long. Dividing into smaller functions would make it easier to read*/
bool Bank::Transfer(Transaction& t, Account*& acct){
    if (t.account_base() == t.account_receive()){
        int fund_0 = (*acct).funds()[0].amount();
        int fund_1 = (*acct).funds()[1].amount();
        int fund_2 = (*acct).funds()[2].amount();
        int fund_3 = (*acct).funds()[3].amount();
        if ((*acct).funds()[t.fund_base()].amount() >= t.amount()){
            (*acct).funds()[t.fund_base()].AddFund(-t.amount());
            (*acct).funds()[t.fund_receive()].AddFund(t.amount());
            t.set_status(true);
            (*acct).funds()[t.fund_receive()].AddHistory(t);
            (*acct).funds()[t.fund_base()].AddHistory(t);
            return true;
        }else if((t.fund_base() == 0 || t.fund_base() == 1) && (fund_0 + fund_1) >= t.amount()){
            Transaction base_0;
            Transaction base_1;
            int amount;
            if (t.fund_base() == 0){
                amount = t.amount() - fund_0;
                base_0.SetTransfer("T", fund_0, t.account_base(), 0, t.account_receive(), t.fund_receive());
                base_0.set_status(true);
                (*acct).funds()[0].AddFund(-fund_0);
                (*acct).funds()[0].AddHistory(base_0);
                base_1.SetTransfer("T", amount, t.account_base(), 1, t.account_receive(), t.fund_receive());
                base_1.set_status(true);
                (*acct).funds()[1].AddFund(-amount);
                (*acct).funds()[1].AddHistory(base_1);
            }else{
                amount = t.amount() - fund_1;
                base_1.SetTransfer("T", fund_1, t.account_base(), 1, t.account_receive(), t.fund_receive());
                base_1.set_status(true);
                (*acct).funds()[1].AddFund(-fund_1);
                (*acct).funds()[1].AddHistory(base_1);
                base_0.SetTransfer("T", amount, t.account_base(), 0, t.account_receive(), t.fund_receive());
                base_0.set_status(true);
                (*acct).funds()[0].AddFund(-amount);
                (*acct).funds()[0].AddHistory(base_0);
            }
                t.set_status(true);
                (*acct).funds()[t.fund_receive()].AddFund(t.amount());
                (*acct).funds()[t.fund_receive()].AddHistory(t);
                return true;
        }else if((t.fund_base() == 2 || t.fund_base() == 3) && (fund_2 + fund_3) >= t.amount()){
            Transaction base_2;
            Transaction base_3;
            int amount;
            if (t.fund_base() == 2){
                amount = t.amount() - fund_2;
                base_2.SetTransfer("T", fund_2, t.account_base(), 2, t.account_receive(), t.fund_receive());
                base_2.set_status(true);
                (*acct).funds()[2].AddFund(-fund_2);
                (*acct).funds()[2].AddHistory(base_2);
                base_3.SetTransfer("T", amount, t.account_base(), 3, t.account_receive(), t.fund_receive());
                base_3.set_status(true);
                (*acct).funds()[3].AddFund(-amount);
                (*acct).funds()[3].AddHistory(base_3);
            }else{
                amount = t.amount() - fund_3;
                base_3.SetTransfer("T", fund_3, t.account_base(), 3, t.account_receive(), t.fund_receive());
                base_3.set_status(true);
                (*acct).funds()[3].AddFund(-fund_3);
                (*acct).funds()[3].AddHistory(base_3);
                base_2.SetTransfer("T", amount, t.account_base(), 2, t.account_receive(), t.fund_receive());
                base_2.set_status(true);
                (*acct).funds()[2].AddFund(-amount);
                (*acct).funds()[2].AddHistory(base_2);
            }
                t.set_status(true);
                (*acct).funds()[t.fund_receive()].AddFund(t.amount());
                (*acct).funds()[t.fund_receive()].AddHistory(t);
                return true;
        }else{
            (*acct).funds()[t.fund_base()].AddHistory(t);
            cerr << "ERROR: Not enough funds to transfer " << t.amount();
            cerr << " from "  << (*acct).customer();
            cerr << (*acct).funds()[t.fund_base()].fund_type();
            cerr <<  " to " << (*acct).funds()[t.fund_receive()].fund_type()<< endl;
            return false;
        }
    }else{
        Account * sec_acct = nullptr;
        accounts_.Retrieve(t.account_receive(), sec_acct);
        if (sec_acct != nullptr){
            int fund_0 = (*acct).funds()[0].amount();
            int fund_1 = (*acct).funds()[1].amount();
            int fund_2 = (*acct).funds()[2].amount();
            int fund_3 = (*acct).funds()[3].amount();
            if ((*acct).funds()[t.fund_base()].amount() >= t.amount()){
                (*acct).funds()[t.fund_base()].AddFund(-t.amount());
                (*sec_acct).funds()[t.fund_receive()].AddFund(t.amount());
                t.set_status(true);
                (*acct).funds()[t.fund_receive()].AddHistory(t);
                (*acct).funds()[t.fund_base()].AddHistory(t);
                return true;
            }else if((t.fund_base() == 0 || t.fund_base() == 1) && (fund_0 + fund_1) >= t.amount()){
                Transaction base_0;
                Transaction base_1;
                int amount;
                if (t.fund_base() == 0){
                    amount = t.amount() - fund_0;
                    base_0.SetTransfer("T", fund_0, t.account_base(), 0, t.account_receive(), t.fund_receive());
                    base_0.set_status(true);
                    (*acct).funds()[0].AddFund(-fund_0);
                    (*acct).funds()[0].AddHistory(base_0);
                    base_1.SetTransfer("T", amount, t.account_base(), 1, t.account_receive(), t.fund_receive());
                    base_1.set_status(true);
                    (*acct).funds()[1].AddFund(-amount);
                    (*acct).funds()[1].AddHistory(base_1);
                }else{
                    amount = t.amount() - fund_1;
                    base_1.SetTransfer("T", fund_1, t.account_base(), 1, t.account_receive(), t.fund_receive());
                    base_1.set_status(true);
                    (*acct).funds()[1].AddFund(-fund_1);
                    (*acct).funds()[1].AddHistory(base_1);
                    base_0.SetTransfer("T", amount, t.account_base(), 0, t.account_receive(), t.fund_receive());
                    base_0.set_status(true);
                    (*acct).funds()[0].AddFund(-amount);
                    (*acct).funds()[0].AddHistory(base_0);
                }
                    (*sec_acct).funds()[t.fund_receive()].AddFund(t.amount());
                    (*sec_acct).funds()[t.fund_receive()].AddHistory(base_0);
                    (*sec_acct).funds()[t.fund_receive()].AddHistory(base_1);

                    // t.set_status(true);
                    // (*sec_acct).funds()[t.fund_receive()].AddFund(t.amount());
                    // (*sec_acct).funds()[t.fund_receive()].AddHistory(t);
                    return true;
            }else if((t.fund_base() == 2 || t.fund_base() == 3) && (fund_2 + fund_3) >= t.amount()){
                Transaction base_2;
                Transaction base_3;
                int amount;
                if (t.fund_base() == 2){
                    amount = t.amount() - fund_2;
                    base_2.SetTransfer("T", fund_2, t.account_base(), 2, t.account_receive(), t.fund_receive());
                    base_2.set_status(true);
                    (*acct).funds()[2].AddFund(-fund_2);
                    (*acct).funds()[2].AddHistory(base_2);
                    base_3.SetTransfer("T", amount, t.account_base(), 3, t.account_receive(), t.fund_receive());
                    base_3.set_status(true);
                    (*acct).funds()[3].AddFund(-amount);
                    (*acct).funds()[3].AddHistory(base_3);
                }else{
                    amount = t.amount() - fund_3;
                    base_3.SetTransfer("T", fund_3, t.account_base(), 3, t.account_receive(), t.fund_receive());
                    base_3.set_status(true);
                    (*acct).funds()[3].AddFund(-fund_3);
                    (*acct).funds()[3].AddHistory(base_3);
                    base_2.SetTransfer("T", amount, t.account_base(), 2, t.account_receive(), t.fund_receive());
                    base_2.set_status(true);
                    (*acct).funds()[2].AddFund(-amount);
                    (*acct).funds()[2].AddHistory(base_2);
                }
                    (*sec_acct).funds()[t.fund_receive()].AddFund(t.amount());
                    (*sec_acct).funds()[t.fund_receive()].AddHistory(base_2);
                    (*sec_acct).funds()[t.fund_receive()].AddHistory(base_3);
                    // t.set_status(true);
                    // (*sec_acct).funds()[t.fund_receive()].AddFund(t.amount());
                    // (*sec_acct).funds()[t.fund_receive()].AddHistory(t);
                    return true;
            }else{
                (*acct).funds()[t.fund_base()].AddHistory(t);
                cerr << "ERROR: Not enough funds to transfer " << t.amount();
                cerr << " from "  << (*acct).customer();
                cerr << (*acct).funds()[t.fund_base()].fund_type();
                cerr <<  " to " << (*acct).funds()[t.fund_receive()].fund_type()<< endl;
                return false;
            }
        }else{
            (*acct).funds()[t.fund_base()].AddHistory(t);
            cerr << "ERROR: Account "<< t.account_receive();
            cerr <<" not found. Transferal refused." << endl;
            return false;
        }
    }
    return true;
}
//Displays specific Account history for all accounts
bool Bank::DisplayAccountHistory(Transaction& t, Account*& acct) const{
    (*acct).DisplayAllFundHistory();
    cout << endl;
    return true;
}
// Displays specific account history
bool Bank::DisplayFundHistory(Transaction& t, Account*& acct) const {
    
    cout << "Transaction History for " << (*acct).customer();
    (*acct).funds()[t.fund_base()].DisplayFundHistory();
    cout << endl;
    return true;
}

// Displays all the account in bank 
void Bank::Display() const{
    cout << "FINAL BALANCES:"<< endl;
    accounts_.Display();

}

