/**
 * This Class part of venting machine that interfaces
 * with the machine to keep track of what kind of coins
 * available and total amount of money based on coin. It
 * can make change based on coins available and adjusts
 * number of coins and total amount once change is made.
 * This class assumes that machine keeps track of it's own
 * capacity and alerts the user separetely.
*/

#ifndef VENDING_BANK_H_
#define VENDING_BANK_H_

#include <iostream>
using namespace std;

class VendingBank{
    
public:
    VendingBank();
    VendingBank(int id);
    // This constructor requires all the coins:
    VendingBank(int id, int quater, int dime, int nickel, int penny);
    
    
    //getters-setters
    int id() const;
    int penny() const;
    int nickel() const;
    int dime() const;
    int quater() const;
    double total_amount() const;
    
    void set_id();
    void set_penny();
    void set_nickel();
    void set_dime();
    void set_quater();
    void set_all_coins(int quater, int dime, int nickel, int penny);
    
    // Note: there is no setter for total_amount_ since it should be
    // based on the coins. If we set the total amount then we do not
    // know what kind of coin types are available.
    
    // This will adjust total amount and necessary coin types:
    // This function could have returned bool and omit bool
    // CanMakeChange function.
    void ReturnChange(double amount);
    
    // This will ensure that there is enough coins type to make a change.
    bool CanMakeChange(double amount) const;
private:
    // id_ is a unique identifier for the VendingBank
    int id_ ;
    double total_amount_;
    int num_pennies_;
    int num_nickels_;
    int num_dimes_;
    int num_quaters_;
    
    
    
    // This would help display what is available
    friend osstream& operator << (osstream& os, const VendingBank& bank);
    // This will help user to interface with this class and set coins
    // and update it when machine is emtied. 
    friend isstream& operator >> (isstream& is, VendingBank& bank);
    
};



#endif /* vending_bank_hpp */
