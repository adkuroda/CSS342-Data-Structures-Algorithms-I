
/** This class hold account information */

#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include "customer.h"
#include <vector>
#include "fund.h"

static const vector<string> FUNDS{"Money Market", "Prime Money Market",
        "Long-Term Bond", "Short-Term Bond", "500 Index Fund",
        "Capital Value Fund", "Growth Equity Fund", "Growth Index Fund"};

class Account{
public:
    Account(const int& id, const string& f_name, const string& l_name);
    Account(const Account& account);
    void DisplayAllFundHistory() const;
    int account_id() const;
    Customer customer() const;
    vector<Fund>& funds();
    
    Account& operator = (const Account& rhs);
    bool operator == (const Account& rhs) const;
    bool operator != (const Account& rhs) const;
    bool operator > (const Account& rhs) const;
    bool operator >= (const Account& rhs) const;
    bool operator < (const Account& rhs) const;
    bool operator <= (const Account& rhs) const;
private:
    int account_id_;
    Customer customer_;
    vector<Fund> funds_;
    friend ostream& operator<< (ostream& os, const Account& rhs);
};

#endif /* account_hpp */
