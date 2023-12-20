#include "customer.h"


Customer::Customer(){
    first_name_ = "";
    last_name_ = ""; 
}

Customer:: Customer(string f_name, string l_name){
    first_name_ = f_name;
    last_name_ = l_name;
}

string Customer::first_name() const{
    return first_name_;
}

string Customer::last_name() const{
    return last_name_;
}

void Customer::set_names(string f_name, string l_name){
    first_name_ = f_name;
    last_name_ = l_name;
}

ostream& operator<<(ostream& os, const Customer& rhs){
    os <<rhs.last_name()  << " " << rhs.first_name() << " ";
    return os;
}
