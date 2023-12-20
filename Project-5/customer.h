
#ifndef CUSTOMER_H_
#define CUSTOMER_H_
#include <string>
#include <ostream>
using namespace std;

class Customer{
public:
    Customer();
    Customer(string f_name, string l_name);
    string first_name() const;
    string last_name() const;
    void set_names(string first_name, string l_name);
    
    
private:
    string first_name_;
    string last_name_;
    friend ostream& operator<<(ostream& os, const Customer& rhs);
};

#endif /* customer_h */
